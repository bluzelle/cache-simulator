#pragma once
#include <kcache/kademlia/kademlia_types.hpp>
#include <kcache/kademlia/kademlia_config.hpp>
#include <actors/simulated_actor.hpp>
#include <random/random.hpp>
#include <vector>
#include <optional>

namespace ksim::kcache
{
    class kademlia_global_state
    {
    public:
        kademlia_global_state(const kademlia_config& config);
        kcache::node_id_t get_new_kid();
        std::list<actor_id_t> get_contacts();
        void register_address(actor_id_t registrant);
        const kademlia_config& config;

        kademlia_global_state(kademlia_global_state const&) = delete;
        kademlia_global_state& operator=(kademlia_global_state const&) = delete;

        kcache::node_id_t chunk_address(chunk_id_t chunk);

    private:
        std::map<chunk_id_t, node_id_t> chunk_mappings;
        std::vector<actor_id_t> known_nodes;
        ksim::random rand;
    };
}

