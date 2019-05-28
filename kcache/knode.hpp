#pragma once
#include <actors/simulated_actor.hpp>

namespace ksim::kcache
{
    class knode : public simulated_actor
    {
    public:
        knode(ksim::actor_system& system);

        void handle_message(const message_t& msg) override;

        void start() override;

    };
}
