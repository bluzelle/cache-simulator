#include <iostream>
#include <sim/simulation.hpp>

using namespace ksim;

simulation::simulation(const sim_config& config)
    : config(config)
    , system(this->config.latency())
{
    std::cout << "Building simulation\n";
    for (int i=0; i<100; i++)
    {
        this->actors.push_back(std::make_unique<knode>(this->system));
    }
}

void simulation::run()
{
    std::cout << "Running simulation\n";
}
