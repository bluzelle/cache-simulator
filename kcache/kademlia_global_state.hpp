#pragma once
#include <kcache/kademlia_types.hpp>
#include <kcache/kademlia_config.hpp>
#include <actors/simulated_actor.hpp>
#include <random>
#include <vector>

namespace ksim::kcache
{
    class kademlia_global_state
    {
    public:
        kademlia_global_state(const kademlia_config& config);
        std::pair<kcache::node_id, std::list<actor_id_t>> introduce(actor_id_t registrant);

    private:
        std::vector<actor_id_t> known_nodes;
        const kademlia_config& config;
        std::mt19937 rand;
    };
}

