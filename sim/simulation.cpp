#include <iostream>
#include <sim/simulation.hpp>
#include <kcache/knode.hpp>
#include <kcache/kclient.hpp>
#include <fstream>
#include <sys/stat.h>

using namespace ksim;

simulation::simulation(sim_config config, const ksim::options& opt)
    : log("simulation", opt)
    , stats(this->log)
    , options(opt)
    , config(std::move(config))
    , system(this->config.latency, this->config.location, this->stats, this->log)
    , algo_config(opt)
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

    this->finalize();
}

void simulation::finalize()
{
    this->system.finalize();
    this->global->finalize(this->stats);

    auto output_root = this->find_output_dir();
    std::experimental::filesystem::create_directory(output_root);

    auto optpath = output_root / std::experimental::filesystem::path("config");
    std::ofstream optfile(optpath);

    optfile << this->options.get();

    this->stats.finalize(output_root);
}

std::experimental::filesystem::path simulation::find_output_dir()
{
    std::experimental::filesystem::path experiment_dir(this->options.get()["name"].asString());
    auto root_output_dir = std::experimental::filesystem::current_path() / std::experimental::filesystem::path("results") / experiment_dir;

    std::experimental::filesystem::create_directories(root_output_dir);

    for(unsigned int i = 0; true; i++)
    {
        if (i > 10000)
        {
            throw std::runtime_error("failed to create output directory");
        }

        auto p2 = root_output_dir / std::experimental::filesystem::path{std::to_string(i)};

        /* we use mkdir() because it errors when the directory already exists; this is not duplicated by filesystem::create_directory
         * we want that behavior because it allows us to run multiple simulations in the same directory without concern:
         * the filesystem will effectively synchronize them because exactly one process will sucessfully create each
         * output directory, so each will be writing to a unique location
         */
        if (mkdir(p2.string().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH))
        {
            continue;
        }

        std::experimental::filesystem::create_directory(p2);
        this->log << "output dir: " << std::string(p2.string()) << "\n";
        return p2;
    }

}