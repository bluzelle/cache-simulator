#pragma once
#include <models/location_model.hpp>
#include <tuple>

namespace ksim
{
    class region_model
    {
    public:
        region_model(const location_model& loc, unsigned int x_count, unsigned int y_count);

        const unsigned int x_cells;
        const unsigned int y_cells;
        const int x_res;
        const int y_res;

        const int x_min;
        const int x_max;
        const int y_min;
        const int y_max;

        using key_t = std::pair<int, int>;

        key_t region_key(location_model::location_t loc) const;
        key_t clip(int x, int y);

        static std::string to_string(key_t);
    };
}
