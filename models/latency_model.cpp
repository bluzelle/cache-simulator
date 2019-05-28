#include "latency_model.hpp"

using namespace ksim;

int
latency_model::latency(const ksim::actor_id_t a, const ksim::actor_id_t b) const
{
    if (a == b)
    {
        return 0;
    }

    return 5; // TODO obviously...
}
