#pragma once
#include <actors/actor_system.hpp>
#include <kcache/knode.hpp>
#include <config/sim_config.hpp>

namespace ksim
{
    class simulation
    {
    public:
        simulation(sim_config config);

        void run();

    private:
        sim_config config;
        actor_system system;

        std::list<std::unique_ptr<simulated_actor>> actors;
    };
}

