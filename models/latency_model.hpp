#pragma once
#include <actors/simulated_actor.hpp>

namespace ksim
{

    class latency_model
    {
    public:
        int latency(const actor_id_t a, const actor_id_t b) const;
    };

}