#include <stats/xy_plot_statistic.hpp>
#include <fstream>

using namespace ksim;

void xy_plot_statistic::record(double x, double y)
{
    this->data.push_back(std::make_pair(x, y));
}

void xy_plot_statistic::report()
{
    std::ofstream data(this->data_path());

    for(const auto& pair : this->data)
    {
        data << pair.first << " " << pair.second << "\n";
    }

    this->write_common_script_prefix();
    std::ofstream script(this->script_path(), std::ios::app);
    script << "plot " << this->data_path() << " with dots\n";
}