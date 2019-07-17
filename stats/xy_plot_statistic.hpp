#pragma once

#include <stats/statistic.hpp>

namespace ksim
{
    class xy_plot_statistic : public statistic
    {
    public:
        xy_plot_statistic(const std::string& name) : statistic(name){}

        void record(double x, double y);

        void report() override;

    private:
        std::vector<std::pair<double, double>> data;
    };
}
