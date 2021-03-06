#pragma once
#include <actors/simulated_actor.hpp>
#include <kcache/kademlia/kademlia_types.hpp>
#include <kcache/kcache_global_state.hpp>
#include <proto/kcache.pb.h>
#include <kcache/kademlia/kademlia_routing_table.hpp>
#include <random/random.hpp>

namespace ksim::kcache
{
    class knode : public simulated_actor
    {
    public:
        knode(ksim::actor_system& system, std::shared_ptr<kcache_global_state> global);

        void start() override;

    private:
        std::shared_ptr<kcache_global_state> global;
    };
}
