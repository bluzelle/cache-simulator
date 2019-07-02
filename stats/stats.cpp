#include <stats/stats.hpp>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <sstream>

using namespace ksim;

void stats::record_data_point(std::string name, double value)
{
    this->data_points[name].push_back(value);
}

std::string stats::to_string()
{
    std::ostringstream ss;
    for (auto& stat : this->data_points)
    {
        std::sort(stat.second.begin(), stat.second.end());
        double median = stat.second[stat.second.size()/2];
        double p10 = stat.second[stat.second.size()/10];
        double p90 = stat.second[stat.second.size()*9/10];
        double p1 = stat.second[stat.second.size()/100];
        double p99 = stat.second[stat.second.size()*99/100];

        double sum = std::accumulate(stat.second.begin(), stat.second.end(), 0);
        double mean = sum / stat.second.size();

        ss << stat.first << ": percentiles ["
                << p1 << "/"
                << p10 << "/"
                << median << "/"
                << p90 << "/"
                << p99 << "]"
                << ", mean " << std::setprecision(4) << mean << "\n";
    }

    return ss.str();
}
