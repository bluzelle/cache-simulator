#pragma once
#include <actors/simulated_actor.hpp>
#include <kcache/kademlia_types.hpp>
#include <kcache/kademlia_global_state.hpp>
#include <proto/kcache.pb.h>

namespace ksim::kcache
{
    class knode : public simulated_actor
    {
    public:
        knode(ksim::actor_system& system, kademlia_global_state& global);

        void handle_message(const message_t& msg) override;

        void start() override;

    private:
        node_id_t k_id;
        std::list<ksim::actor_id_t> introduction_points;

        void handle_ping(const kcache_ping& msg);
        void handle_ping_response(const kcache_ping_response& msg);
        void handle_find_neighborhood(const kcache_find_neighborhood& msg);
        void handle_find_neighborhood_response(const kcache_find_neighborhood_response& msg);
    };
}
