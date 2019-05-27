#pragma once
#include <actors/simulated_actor.hpp>

namespace ksim
{
    class knode : public simulated_actor
    {
        void handle_message(const message_t& msg) override;
    };
}
