#include <stats/statistic_set.hpp>
#include <fstream>

using namespace ksim;

statistic_set::statistic_set(log_base& log_parent)
    : log("statistic set", log_parent)
{
}

void
statistic_set::finalize(const std::experimental::filesystem::path& path)
{
    auto summary_path = path / std::experimental::filesystem::path{"summary.txt"};
    std::ofstream summary_stream(summary_path);

    this->log << "writing report data to " << path.string() << "\n";
    this->log << "writing summary statistics to " << summary_path.string() << "\n";

    auto script_path = path / std::experimental::filesystem::path("generate_graphs");
    auto graphs_path = path / std::experimental::filesystem::path("graphs");
    std::ofstream ss(script_path);
    ss << "mkdir -p " << graphs_path << "\n";

    for(const auto& stat: this->stats){
        std::string fname = stat.first;
        while(fname.find(" ") != std::string::npos)
        {
            fname.replace(fname.find(" "), 1, "_");
        }

        auto stat_dir = path / std::experimental::filesystem::path{fname};
        std::experimental::filesystem::create_directory(stat_dir);

        stat.second->set_path(stat_dir);
        stat.second->finalize();
        stat.second->summarize(summary_stream);
        stat.second->report();

        if(stat.second->graph_generated())
        {
            ss << "gnuplot " << stat.second->script_path() << "\n";
            ss << "cp " << stat.second->graph_path();
            ss << " " << (graphs_path / std::experimental::filesystem::path(fname + ".png")) << "\n";
        }
    }

    std::experimental::filesystem::permissions(script_path, std::experimental::filesystem::perms::owner_exec | std::experimental::filesystem::perms::add_perms);
}

void
statistic_set::update_time(unsigned long new_time)
{
    this->time = new_time;
    for(const auto& stat_pair : this->stats)
    {
        stat_pair.second->update_time(new_time);
    }
}

