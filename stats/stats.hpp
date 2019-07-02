#pragma once
#include <string>
#include <vector>
#include <map>

namespace ksim
{
    class stats {
    public:
        void record_data_point(std::string name, double value);

        std::string to_string();

    private:
        std::map<std::string, std::vector<double>> data_points;
    };
}
