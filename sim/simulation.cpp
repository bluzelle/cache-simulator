#include <iostream>
#include <sim/simulation.hpp>
#include <kcache/knode.hpp>
#include <kcache/kclient.hpp>

using namespace ksim;

simulation::simulation(sim_config config)
    : config(std::move(config))
    , system(this->config.latency, this->config.location, this->stats)
    , global(std::make_shared<kcache::kcache_global_state>(this->algo_config))
{
    this->log.say("building simulation");
    for (int i=0; i<this->config.nodes_count; i++)
    {
        this->actors.push_back(std::make_unique<kcache::knode>(this->system, this->global));
    }
    
    for (int i=0; i<this->config.clients_count; i++)
    {
        this->actors.push_back(std::make_unique<kcache::kclient>(this->system, this->global, this->config.clients));
    }
}

void simulation::run()
{
    this->log.say("running simulation");
    for (auto& actor : this->actors)
    {
        actor->start();
    }

    this->system.run_until(this->config.duration);
    this->system.finalize();

    this->log.say("\n\nfinal stats");
    this->stats.finalize();
}
