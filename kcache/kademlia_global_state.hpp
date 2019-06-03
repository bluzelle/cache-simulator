#pragma once
#include <kcache/kademlia_types.hpp>
#include <kcache/kademlia_config.hpp>
#include <actors/simulated_actor.hpp>
#include <random/random.hpp>
#include <vector>

namespace ksim::kcache
{
    class kademlia_global_state
    {
    public:
        kademlia_global_state(const kademlia_config& config);
        std::pair<kcache::node_id_t, std::list<actor_id_t>> introduce(actor_id_t registrant);
        const kademlia_config& config;

    private:
        std::vector<actor_id_t> known_nodes;
        ksim::random rand;
    };
}

