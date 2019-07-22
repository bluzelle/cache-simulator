#pragma once

#include <models/latency_model.hpp>
#include <models/client_model.hpp>
#include <options/options.hpp>

namespace ksim
{
    class sim_config
    {
    public:
        sim_config(const options&);

        const int clients_count;
        const int nodes_count;

        const long duration;
        const latency_model latency;
        location_model location;
        client_model clients;
    };
}
