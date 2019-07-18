#pragma once
#include <kcache/kademlia/kademlia_types.hpp>
#include <kcache/kcache_config.hpp>
#include <actors/simulated_actor.hpp>
#include <random/random.hpp>
#include <vector>
#include <optional>

namespace ksim::kcache
{
    class kcache_global_state
    {
        /*
         * Of course, a proper kademlia implementation does not have any global state.
         * This class is for those elements which I am not simulating for the sake of simplicity.
         */

    public:
        kcache_global_state(const kcache_config& config);
        kcache::node_id_t get_new_kid();
        std::list<actor_id_t> get_contacts();

        void register_address(actor_id_t registrant);
        void register_kid_for_storage(actor_id_t address, node_id_t kid);

        void start_caching(actor_id_t actor, chunk_id_t chunk);
        void stop_caching(actor_id_t actor, chunk_id_t chunk);

        const std::set<actor_id_t>& find_authoratitive_stores(chunk_id_t);
        const std::set<actor_id_t>& find_caches(chunk_id_t);

        void finalize(ksim::statistic_set& stats);

        const kcache_config& config;

        kcache_global_state(kcache_global_state const&) = delete;
        kcache_global_state& operator=(kcache_global_state const&) = delete;

        kcache::node_id_t chunk_address(chunk_id_t chunk);

    private:
        std::map<chunk_id_t, std::set<actor_id_t>> authoratitive_store_locations;
        std::map<chunk_id_t, std::set<actor_id_t>> cache_locations;
        std::map<actor_id_t, node_id_t> known_storage_kids;

        std::map<chunk_id_t, node_id_t> chunk_mappings;
        std::vector<actor_id_t> known_nodes;
        ksim::random rand;
    };
}

