#pragma once

#include <models/latency_model.hpp>

namespace ksim
{
    class sim_config
    {
    public:
        sim_config();

        const int nodes_count = 2000;
        const long duration = 100000;
        const latency_model latency;
        const location_model location;
    };
}
