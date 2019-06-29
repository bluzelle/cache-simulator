#pragma once
#include <actors/activity.hpp>
#include <kcache/kademlia/kademlia_routing_table.hpp>
#include <kcache/kademlia/kademlia_types.hpp>
#include <kcache/kademlia/kademlia_global_state.hpp>
#include <proto/kcache.pb.h>
#include <random/random.hpp>
#include <include/types.hpp>

namespace ksim::kcache{
    class kademlia_activity : public activity {

    public:
        kademlia_activity(simulated_actor* owner, unsigned int id,
                          std::shared_ptr<kademlia_global_state> global, bool advertise, std::optional<node_id_t> known_kid = std::nullopt);

        void start() override;
        void handle_message(const userspace_message_t& msg) override;
        bool handles_message(const userspace_message_t& msg) override;
        void finalize() override;

    private:
        void handle_ping(const kcache_message& header, const kcache_ping& msg);
        void handle_ping_response(const kcache_message& header, const kcache_ping_response& msg);
        void handle_ping_response_2(const kcache_message& header, const kcache_ping_response_2& msg);
        void handle_find_neighborhood(const kcache_message& header, const kcache_find_neighborhood& msg);
        void handle_find_neighborhood_response(const kcache_message& header, const kcache_find_neighborhood_response& msg);

        void do_gossip();
        void ingest(const kcache_node_reference& peer);
        userspace_message_t finalize(const kcache_message& msg);
        void finalize_and_send_message(actor_id_t target, kcache_message& msg);
        void finalize_and_reply(kcache_message& msg);

        const bool advertise;
        const node_id_t k_id;
        std::list<ksim::actor_id_t> seed_peers;
        kademlia_routing_table peers;
        ksim::random rand;
        const kademlia_config& config;
    };
}

