#pragma once
#include <random/random.hpp>
#include <vector>

namespace ksim
{
    class location_model
    {
    public:
        // x, y, z, compute distance in the x-y plane and add z as a constant extra latency
        using location = std::tuple<float, float, float>;

        location pick_location();

    private:

        location select_location();

        random rand;

        std::vector<location> placed_locations;

        const double xmin = -200;
        const double xmax = 200;
        const double ymin = -200;
        const double ymax = 200;
        const double zmin = 0;
        const double zmax = 50;

        const float break_chance = 0.07;
        const float city_radius = 7;
        unsigned int min_sites = 20;
    };
}

