#include <stats/statistic.hpp>
#include <cassert>
#include <fstream>

using namespace ksim;

statistic::statistic(const std::string& name)
    : name(name)
{}

void
statistic::update_time(unsigned long new_time)
{
    this->current_time = new_time;
}

void
statistic::set_path(const std::experimental::filesystem::path& path)
{
    this->root_path = path;
}


std::experimental::filesystem::path
statistic::named_path(const std::string& name)
{
    assert(this->root_path.string().size() > 1);
    return this->root_path / std::experimental::filesystem::path(name);
}

std::experimental::filesystem::path statistic::graph_path()
{
    this->graph_path_used = true;
    return this->named_path("chart.png");
}

std::experimental::filesystem::path statistic::data_path(const std::string& name)
{
    return this->named_path(name);
}

std::experimental::filesystem::path statistic::script_path()
{
    return this->named_path("generate.gnuplot");
}

bool statistic::graph_generated()
{
    return this->graph_path_used;
}

void statistic::write_common_script_prefix()
{
    std::ofstream ss(this->script_path());

    ss << "set term png size 1280, 960\n";
    ss << "set output " << this->graph_path() << "\n";
    ss << "set title '" << this->name << "'\n";

}