#pragma once
#include <random/random.hpp>
#include <vector>

namespace ksim
{
    class location_model
    {
    public:
        // x, y, z, compute distance in the x-y plane and add z as a constant extra latency
        using location_t = std::tuple<float, float, float>;

        location_t pick_location();

        const double xmin = -200;
        const double xmax = 200;
        const double ymin = -200;
        const double ymax = 200;
        const double zmin = 0;
        const double zmax = 50;

    private:

        location_t select_location();

        random rand;

        std::vector<location_t> placed_locations;

        const float break_chance = 0.07;
        const float city_radius = 7;
        unsigned int min_sites = 20;
    };
}
