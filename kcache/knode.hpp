#pragma once
#include <actors/simulated_actor.hpp>

namespace ksim
{
    class knode : public simulated_actor
    {
    public:
        knode(ksim::actor_system& system);

        void handle_message(const message_t& msg) override;

    };
}
