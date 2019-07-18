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

    this->finalize();
}

void simulation::finalize()
{
    this->system.finalize();
    this->global->finalize(this->stats);

    auto output_root = this->find_output_dir();
    std::experimental::filesystem::create_directory(output_root);

    this->stats.finalize(output_root);
}

std::experimental::filesystem::path simulation::find_output_dir()
{
    auto root_output_dir = std::experimental::filesystem::current_path() / std::experimental::filesystem::path("results");

    if(std::experimental::filesystem::exists(root_output_dir) && !std::experimental::filesystem::is_directory(root_output_dir))
    {
        throw std::runtime_error("output dir is not a dir");
    }

    if(!std::experimental::filesystem::exists(root_output_dir))
    {
        std::experimental::filesystem::create_directory(root_output_dir);
    }

    for(unsigned int i = 0; true; i++)
    {
        auto p2 = root_output_dir / std::experimental::filesystem::path{std::to_string(i)};
        if (!std::experimental::filesystem::exists(p2))
        {
            std::experimental::filesystem::create_directory(p2);
            this->log << "output dir: " << std::string(p2.string()) << "\n";
            return p2;
        }
    }

}