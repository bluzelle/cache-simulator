#pragma once
#include <actors/actor_system.hpp>
#include <kcache/knode.hpp>
#include <kcache/kademlia/kademlia_global_state.hpp>
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

        kcache::kademlia_config algo_config;
        std::shared_ptr<kcache::kademlia_global_state> global;

        std::list<std::unique_ptr<simulated_actor>> actors;
    };
}

