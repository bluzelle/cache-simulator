#pragma once
#include <actors/simulated_actor.hpp>
#include <kcache/kademlia_types.hpp>
#include "kademlia_global_state.hpp"

namespace ksim::kcache
{
    class knode : public simulated_actor
    {
    public:
        knode(ksim::actor_system& system, kademlia_global_state& global);

        void handle_message(const message_t& msg) override;

        void start() override;

    private:
        node_id id;
        std::list<ksim::simulated_actor*> introduction_points;
    };
}
