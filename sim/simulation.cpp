#include <iostream>
#include <sim/simulation.hpp>
#include <kcache/knode.hpp>

using namespace ksim;

simulation::simulation(sim_config config)
    : config(std::move(config))
    , system(this->config.latency)
    , global(this->algo_config)
{
    std::cout << "Building simulation\n";
    for (int i=0; i<this->config.nodes_count; i++)
    {
        this->actors.push_back(std::make_unique<kcache::knode>(this->system, this->global));
    }
}

void simulation::run()
{
    std::cout << "Running simulation\n";
    for (auto& actor : this->actors)
    {
        actor->start();
    }

    this->system.run_until(this->config.duration);
}
