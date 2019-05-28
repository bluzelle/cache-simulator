#include <config/sim_config.hpp>

using namespace ksim;

int
sim_config::nodes_count()
{
    return 1000;
}

latency_model&
sim_config::latency()
{
    return this->inner_latency;
}
