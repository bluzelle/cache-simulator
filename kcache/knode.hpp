#pragma once
#include <actors/simulated_actor.hpp>
#include <kcache/kademlia_types.hpp>
#include <kcache/kademlia_global_state.hpp>
#include <proto/kcache.pb.h>
#include <kcache/kademlia_routing_table.hpp>
#include <random/random.hpp>

namespace ksim::kcache
{
    class knode : public simulated_actor
    {
    public:
        knode(ksim::actor_system& system, kademlia_global_state& global);

        void handle_message(const userspace_message_t& msg) override;

        void start() override;

        void finalize() override;

    private:
        std::pair<node_id_t, std::list<ksim::actor_id_t>> introduction;
        node_id_t k_id;
        kademlia_routing_table peers;
        ksim::random rand;
        const kademlia_config& config;

        void handle_ping(const kcache_message& header, const kcache_ping& msg);
        void handle_ping_response(const kcache_message& header, const kcache_ping_response& msg);
        void handle_ping_response_2(const kcache_message& header, const kcache_ping_response_2& msg);
        void handle_find_neighborhood(const kcache_message& header, const kcache_find_neighborhood& msg);
        void handle_find_neighborhood_response(const kcache_message& header, const kcache_find_neighborhood_response& msg);
        void handle_timer(const kcache_message& header, const kcache_timer& msg);

        void do_gossip();
        void ingest(const kcache_node_reference& peer);
        void finalize_and_send_message(actor_id_t target, kcache_message& msg);

        void log(const std::string& msg);
    };
}
