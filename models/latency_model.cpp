#include "latency_model.hpp"

using namespace ksim;

int
latency_model::latency(const ksim::simulated_actor* a, const ksim::simulated_actor* b) const
{
    if (a == b)
    {
        return 0;
    }

    return 5; // TODO obviously...
}
