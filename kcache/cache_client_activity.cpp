#include <kcache/cache_client_activity.hpp>

using namespace ksim::kcache;

cache_client_activity::cache_client_activity(ksim::simulated_actor *owner, unsigned int id,
                                             std::shared_ptr<ksim::kcache::kcache_global_state> global)

    : activity(owner, id)
    , global(global)
{
}

void
cache_client_activity::start()
{
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
                    this->closest_authoratative_source = std::min(this->closest_authoratative_source, latency);
                    break;
                case ping_type::cache:
                    this->closest_cache = std::min(this->closest_cache, latency);
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
    for (const auto& address: this->global->find_authoratitive_stores(this->work.chunk))
    {
        this->maybe_ping(address, ping_type::authoratitive);
    }

    for (const auto& address: this->global->find_caches(this->work.chunk))
    {
        this->maybe_ping(address, ping_type::cache);
    }

    this->start_timer(this->global->config.client_cache_request_interval, [&](){this->tick();});

    throw std::runtime_error("send requests!");
}

void
cache_client_activity::finalize()
{
    std::cout << "Client of chunk " << this->work.chunk
              << " using authoratitive source at " << this->closest_authoratative_source
              << " rtt and cache at " << this->closest_cache
              << " rtt\n";
}


