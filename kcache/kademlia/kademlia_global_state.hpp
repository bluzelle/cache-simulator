#pragma once
#include <kcache/kademlia/kademlia_types.hpp>
#include <kcache/kademlia/kademlia_config.hpp>
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

        kademlia_global_state(kademlia_global_state const&) = delete;
        kademlia_global_state& operator=(kademlia_global_state const&) = delete;

    private:
        std::vector<actor_id_t> known_nodes;
        ksim::random rand;
    };
}

