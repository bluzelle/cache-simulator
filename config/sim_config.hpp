#pragma once

#include <models/latency_model.hpp>

namespace ksim
{
    class sim_config
    {
    public:
        int nodes_count();
        latency_model& latency();
    private:
        latency_model inner_latency;
    };
}
