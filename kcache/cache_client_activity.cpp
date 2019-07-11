#include <kcache/cache_client_activity.hpp>

using namespace ksim::kcache;

cache_client_activity::cache_client_activity(ksim::simulated_actor *owner, unsigned int id,
                                             std::shared_ptr<ksim::kcache::kcache_global_state> global,
                                             std::shared_ptr<ksim::kcache::kademlia_activity> kademlia,
                                             const client_work_spec& work)

    : activity(owner, id)
    , work(work)
    , global(global)
    , kademlia(kademlia)
{
}

void
cache_client_activity::start()
{
    this->log << "client for chunk " << this->work.chunk << " starting\n";
    auto time = this->rand.next_int_inclusive(0ul, this->global->config.client_cache_request_interval);
    this->start_timer(time, [&](){this->tick();});
}

void
cache_client_activity::handle_message(const ksim::userspace_message_t& msg)
{
    cache_finding_message parsed;
    parsed = msg.cache_finding_message();

    switch (parsed.payload_case())
    {
        case cache_finding_message::kPing:
        {
            auto latency = this->current_time() - parsed.ping().start_time();
            this->known_latencies[parsed.ping().target()] = latency;

            switch (parsed.ping().type()) {
                case ping_type::authoratitive:
                    if(latency < this->closest_authoratative_source_latency)
                    {
                        this->log << "new auth source at " << parsed.ping().target() << " latency " << latency << "\n";
                        this->closest_authoratative_source = parsed.ping().target();
                        this->closest_authoratative_source_latency = latency;
                    }
                    break;
                case ping_type::cache:
                    if(latency < this->closest_cache_latency)
                    {
                        this->log << "new cache source at " << parsed.ping().target() << " latency " << latency << "\n";
                        this->closest_cache = parsed.ping().target();
                        this->closest_cache_latency = latency;
                    }
                    break;
                default:
                    throw std::runtime_error("unknown ping type");
            }
            break;
        }
        default:
            throw std::runtime_error("unknown message type");
    }
}

void
cache_client_activity::maybe_ping(ksim::actor_id_t target, ping_type type)
{
    if(this->known_latencies.count(target) == 0)
    {
        this->log << "sending ping to " << target << "\n";
        userspace_message_t msg;
        auto ptr = msg.mutable_cache_finding_message()->mutable_ping();
        ptr->set_type(type);
        ptr->set_target(target);
        ptr->set_start_time(this->current_time());
        this->send_activity_message(target, msg);
    }
}

void
cache_client_activity::tick()
{
    this->log.say("tick");
    for (const auto& address: this->global->find_authoratitive_stores(this->work.chunk))
    {
        this->maybe_ping(address, ping_type::authoratitive);
    }

    for (const auto& address: this->global->find_caches(this->work.chunk))
    {
        this->maybe_ping(address, ping_type::cache);
    }

    this->start_timer(this->global->config.client_cache_request_interval, [&](){this->tick();});

    auto targets = this->kademlia->routing_table().peers_closer_than(std::min(this->closest_cache_latency, this->closest_authoratative_source_latency));
    for(const auto& peer : targets)
    {
        this->log << "sending speculative upgrade request to " << peer.second << "\n";
        this->send_speculative_request(peer.second);
    }

    if(this->closest_cache_latency < ULONG_MAX)
    {
        // We need to send a request to our current cache as well to make sure it doesn't drop our data. This
        // is a simplification for a real cache node's inferring this behavior from real requests, which we do not
        // perform.
        //
        // There is no possibility that this is a duplicate request, because the ones we already sent are to nodes with
        // exclusively a lower latency.
        this->log << "sending speculative upkeep request to " << this->closest_cache << "\n";
        this->send_speculative_request(this->closest_cache);
    }
}

void
cache_client_activity::finalize()
{
    this->log << "Client of chunk " << this->work.chunk
              << " using authoratitive source at " << this->closest_authoratative_source_latency
              << " rtt and cache at " << this->closest_cache_latency
              << " rtt on actors " << this->closest_authoratative_source << ", " << this->closest_cache << "\n";

    this->stats().record_data_point("final authoratitive latency", this->closest_authoratative_source_latency);
    this->stats().record_data_point("final cache latency", std::min(this->closest_authoratative_source_latency, this->closest_cache_latency));

    //force to double so that negative differences work
    this->stats().record_data_point("final cache advantage", (1.0*this->closest_authoratative_source_latency) - (1.0*std::min(this->closest_authoratative_source_latency, this->closest_cache_latency)));
}

void
cache_client_activity::send_speculative_request(ksim::actor_id_t target)
{
    userspace_message_t msg;
    msg.mutable_cache_finding_message()->mutable_cache_request()->set_chunk_id(this->work.chunk);
    msg.mutable_cache_finding_message()->mutable_cache_request()->set_frequency(this->work.requests_per_unit_time);
    this->send_activity_message(target, msg);
}

