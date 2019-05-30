#pragma once
#include <random/random.hpp>

namespace ksim
{
    class location_model
    {
    public:
        // x, y, z, compute distance in the x-y plane and add z as a constant extra latency
        using location = std::tuple<int, int, int>;

        location_model();

        location pick_location();

    private:
        random rand;
    };
}

