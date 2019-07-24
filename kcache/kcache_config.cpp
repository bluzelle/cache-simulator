#include <kcache/kcache_config.hpp>

using namespace ksim::kcache;

kcache_config::kcache_config(const options& opt)
    : cache_choice_update_interval(opt.get()["kcache_options"]["cache_choice_update_interval"].asUInt64())
    , client_cache_request_interval(opt.get()["kcache_options"]["speculative_cache_request_interval"].asUInt64())
    , authoratitive_copies(opt.get()["kcache_options"]["authoratitive_copies_per_chunk"].asUInt64())
    , peers_bucket_size(opt.get()["kcache_options"]["bucket_size"].asUInt64())
    , gossip_time_min(opt.get()["kcache_options"]["kademlia_gossip_time_min"].asUInt64())
    , gossip_time_max(opt.get()["kcache_options"]["kademlia_gossip_time_max"].asUInt64())
    , cache_chunks_per_node(opt.get()["kcache_options"]["cache_chunks_per_node"].asUInt64())
{
}

