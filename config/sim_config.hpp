#pragma once

#include <models/latency_model.hpp>

namespace ksim
{
    class sim_config
    {
    public:
        sim_config();

        const int nodes_count = 5;
        const long duration = 10000;
        const latency_model latency;
    };
}
