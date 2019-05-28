#pragma once
#include <actors/simulated_actor.hpp>

namespace ksim
{

    class latency_model
    {
    public:
        int latency(const simulated_actor* a, const simulated_actor* b) const;
    };

}