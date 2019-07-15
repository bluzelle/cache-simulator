#include <stats/statistic_set.hpp>
#include <fstream>

using namespace ksim;

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

        stat.second->finalize();
        stat.second->summarize(summary_stream);
        stat.second->report(stat_dir);

        if(stat.second->generates_graph())
        {
            ss << "gnuplot " << (stat_dir / std::experimental::filesystem::path("script.gnuplot")) << "\n";
            ss << "cp " << (stat_dir / std::experimental::filesystem::path("graph.png"));
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

