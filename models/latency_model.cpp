#include "latency_model.hpp"
#include <cmath>

using namespace ksim;

int
latency_model::latency(const simulated_actor& a, const simulated_actor& b) const
{
    // minimum of 1 because messages should never be sent and delivered in the same tick

    if (a.id == b.id)
    {
        return 1;
    }

    auto xdist = std::get<0>(a.location) - std::get<0>(b.location);
    auto ydist = std::get<1>(a.location) - std::get<1>(b.location);
    auto zdist = std::get<2>(a.location) + std::get<2>(b.location);

    auto res_float = std::sqrt(xdist*xdist + ydist*ydist) + zdist;

    return 1 + std::round(res_float);
}
