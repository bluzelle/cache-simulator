#include <iostream>
#include <sim/simulation.hpp>
#include <kcache/knode.hpp>

using namespace ksim;

simulation::simulation(sim_config config)
    : config(std::move(config))
    , system(this->config.latency)
{
    std::cout << "Building simulation\n";
    for (int i=0; i<100; i++)
    {
        this->actors.push_back(std::make_unique<kcache::knode>(this->system));
    }
}

void simulation::run()
{
    std::cout << "Running simulation\n";
    this->system.run_until(this->config.duration);
}
