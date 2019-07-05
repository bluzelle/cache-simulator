#pragma once

#include <models/latency_model.hpp>
#include <models/client_model.hpp>

namespace ksim
{
    class sim_config
    {
    public:
        sim_config();

        const int clients_count = 30000;
        const int nodes_count = 6000;

        const long duration = 300000;
        const latency_model latency;
        location_model location;
        client_model clients;
    };
}
