#pragma once

#include <config/alg_specific_config.hpp>

namespace ksim::kcache
{
    class kcache_config : ksim::alg_specific_config
    {
    public:

        const unsigned long cache_choice_update_interval = 10000;
        const unsigned long client_cache_request_interval = 10000;

        const unsigned int replication_factor = 3;
        const unsigned int gossip_time_min = 4500;
        const unsigned int gossip_time_max = 5500;

        const unsigned int cache_chunks_per_node = 8;
    };

}
