#pragma once
#include <actors/actor_system.hpp>
#include <kcache/knode.hpp>
#include <kcache/kcache_global_state.hpp>
#include <config/sim_config.hpp>
#include <stats/statistic_set.hpp>
#include <log/log.hpp>
#include <experimental/filesystem>
#include <options/options.hpp>

namespace ksim
{
    class simulation
    {
    private:
        ksim::log_root log;

    public:
        simulation(sim_config config, const options& opt);

        void run();

        statistic_set stats;

    private:
        void finalize();

        std::experimental::filesystem::path find_output_dir();

        const ksim::options& options;

        sim_config config;
        actor_system system;

        kcache::kcache_config algo_config;
        std::shared_ptr<kcache::kcache_global_state> global;

        std::list<std::unique_ptr<simulated_actor>> actors;

    };
}

