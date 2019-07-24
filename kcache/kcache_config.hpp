#pragma once

#include <config/alg_specific_config.hpp>
#include <options/options.hpp>

namespace ksim::kcache
{
    class kcache_config : ksim::alg_specific_config
    {
    public:
        kcache_config(const ksim::options& opt);

        const unsigned long cache_choice_update_interval;
        const unsigned long client_cache_request_interval;

        const unsigned int authoratitive_copies;
        const unsigned int peers_bucket_size;
        const unsigned int gossip_time_min;
        const unsigned int gossip_time_max;

        const unsigned int cache_chunks_per_node;
    };

}
