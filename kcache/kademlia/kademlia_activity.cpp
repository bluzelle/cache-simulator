#include <kcache/kademlia/kademlia_activity.hpp>

using namespace ksim::kcache;

kademlia_activity::kademlia_activity(simulated_actor* owner, unsigned int id,
                                     std::shared_ptr<kcache_global_state> global, bool advertise, std::optional<node_id_t> known_kid)
        : activity(owner, id)
        , advertise(advertise)
        , k_id(known_kid.value_or(global->get_new_kid()))
        , seed_peers(global->get_contacts())
        , peers(this->k_id, global->config.replication_factor)
        , config(global->config)
{
    if(advertise)
    {
        global->register_address(this->address());
    }
}

bool
kademlia_activity::handles_message(const ksim::userspace_message_t &msg)
{
    return msg.payload_case() == userspace_message_t::kKcacheMessage;
}

void
kademlia_activity::handle_message(const ksim::userspace_message_t& msg)
{
    kcache_message parsed;
    parsed = msg.kcache_message();

    switch (parsed.payload_case())
    {
        case kcache_message::kPing:
            this->handle_ping(parsed, parsed.ping());
            break;
        case kcache_message::kPingResponse:
            this->handle_ping_response(parsed, parsed.ping_response());
            break;
        case kcache_message::kPingResponse2:
            this->handle_ping_response_2(parsed, parsed.ping_response_2());
            break;
        case kcache_message::kFindNeighborhood:
            this->handle_find_neighborhood(parsed, parsed.find_neighborhood());
            break;
        case kcache_message::kFindNeighborhoodResponse:
            this->handle_find_neighborhood_response(parsed, parsed.find_neighborhood_response());
            break;
        default:
            break;
    }
    // Two RPCS- find-nearby and ping
    // find-nearby: ingest sender and give me the r k-closest node
    // ping: respond with time

    // at startup, find-nearby(my address) at all the introducer nodes

    // every second, pick a node at random from the routing table and find-nearby(my address) at it
    // on find-nearby-response, ingest every node in response
    // on ping-response, insert into routing table if appropriate

    // ingest: if it's not already in my rounting table, send it a ping

    // optionally: to accelerate the process of building the initial table, do some kind of special
    // case shortly after startup. But also that probably isn't necessary...
}

void kademlia_activity::handle_ping(const kcache_message& /*header*/, const kcache_ping& msg)
{
    //this->log("got ping from " + std::to_string(header.sender().kid()));
    kcache_message resp;
    resp.mutable_ping_response()->set_start_time(msg.start_time());
    resp.mutable_ping_response()->set_start_time_2(this->current_time());
    this->finalize_and_reply(resp);
}

void kademlia_activity::handle_ping_response(const kcache_message& header, const kcache_ping_response& msg)
{
    //this->log("got ping response from " + std::to_string(header.sender().kid()));
    this->peers.insert(header.sender().kid(), header.sender().address(), this->current_time() - msg.start_time());

    kcache_message resp;
    if(this->advertise)
    {
        resp.mutable_ping_response_2()->set_start_time_2(msg.start_time_2());
        this->finalize_and_reply(resp);
    }
}

void kademlia_activity::handle_ping_response_2(const kcache_message& header, const kcache_ping_response_2& msg)
{
    //this->log("got ping response 2 from " + std::to_string(header.sender().kid()));
    this->peers.insert(header.sender().kid(), header.sender().address(), this->current_time() - msg.start_time_2());
}

void kademlia_activity::handle_find_neighborhood(const kcache_message& /*header*/, const kcache_find_neighborhood& msg)
{
    //this->log("got find neighborhood from " + std::to_string(header.sender().kid()));

    kcache_message resp;
    resp.mutable_find_neighborhood_response()->set_target_kid(msg.target_kid());

    auto reformat = [](const kademlia_routing_table::peer_record_t& p, kcache_node_reference* dest)
    {
        dest->set_kid(p.first);
        dest->set_address(p.second);
    };

    for (const auto& peer : this->peers.k_nearest(msg.target_kid()))
    {
        reformat(peer, resp.mutable_find_neighborhood_response()->mutable_closest_nodes()->Add());
    }

    for (const auto& peer : this->peers.random())
    {
        reformat(peer, resp.mutable_find_neighborhood_response()->mutable_random_nodes()->Add());
    }

    this->finalize_and_reply(resp);
}

void kademlia_activity::handle_find_neighborhood_response(const kcache_message& /*header*/, const kcache_find_neighborhood_response& msg)
{
    //this->log("got find neighborhood response " + std::to_string(header.sender().kid()));
    std::set<actor_id_t> dedup;

    auto consider = [&](const kcache_node_reference& peer)
    {
        if (dedup.count(peer.address()) == 0)
        {
            dedup.insert(peer.address());
            this->ingest(peer);
        }
    };

    for (const auto& peer : msg.closest_nodes())
    {
        consider(peer);
    }

    for (const auto& peer : msg.random_nodes())
    {
        consider(peer);
    }
}

void kademlia_activity::do_gossip()
{
    for (const auto& peer : this->peers.random())
    {
        kcache_message request;
        request.mutable_find_neighborhood()->set_target_kid(this->k_id);
        this->finalize_and_send_message(peer.second, request);
    }

    this->start_timer(
            this->rand.next_int_inclusive(this->config.gossip_time_min, this->config.gossip_time_max),
            [&](){this->do_gossip();});
}

ksim::userspace_message_t
kademlia_activity::finalize(const kcache_message& msg)
{
    ksim::userspace_message_t env;
    env.set_allocated_kcache_message(new kcache_message(msg));
    env.mutable_kcache_message()->mutable_sender()->set_address(this->address());
    env.mutable_kcache_message()->mutable_sender()->set_kid(this->k_id);
    return env;
}

void kademlia_activity::finalize_and_send_message(actor_id_t target, kcache_message& msg)
{
    this->send_activity_message(target, this->finalize(msg));
}

void
kademlia_activity::finalize_and_reply(kcache_message& msg)
{
    this->reply_in_context(this->finalize(msg));
}

void kademlia_activity::ingest(const kcache_node_reference& peer)
{
    //this->log("considering connection with " + std::to_string(peer.kid()));
    if (!this->peers.contains(peer.kid(), peer.address()) && peer.address() != this->address())
    {
        //this->log("sending ping");
        kcache_message ping;
        ping.mutable_ping()->set_start_time(this->current_time());
        this->finalize_and_send_message(peer.address(), ping);
    }
}

void kademlia_activity::start()
{
    for (auto peer : this->seed_peers)
    {
        if (peer != this->address())
        {
            kcache_message ping;
            ping.mutable_ping()->set_start_time(this->current_time());
            this->finalize_and_send_message(peer, ping);
        }
    }

    this->start_timer(
            this->rand.next_int_inclusive(this->config.gossip_time_min, this->config.gossip_time_max),
            [&](){this->do_gossip();});
}

void kademlia_activity::finalize()
{
    std::cout << "kademlia activity with id " << this->k_id << " advertisement " << this->advertise << "\n";
    std::cout << this->peers.to_s();
}

const kademlia_routing_table& kademlia_activity::routing_table()
{
    return this->peers;
}

node_id_t kademlia_activity::get_k_id()
{
    return this->k_id;
}