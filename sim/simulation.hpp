#pragma once
#include <actors/actor_system.hpp>
#include <kcache/knode.hpp>

namespace ksim
{
    class simulation
    {
    public:
        simulation();

        void run();

    private:
        actor_system system;
        std::list<std::unique_ptr<simulated_actor>> actors;
    };
}

