#include <kcache/knode.hpp>
#include <kcache/kademlia/kademlia_activity.hpp>
#include <actors/simulated_actor.hpp>
#include <iostream>
#include <proto/kcache.pb.h>

using namespace ksim::kcache;

knode::knode(actor_system& system, std::shared_ptr<kademlia_global_state> global)
        : simulated_actor(system)
        , global(global)
{
}

void knode::start()
{
    this->start_activity<kademlia_activity>(this->global);
}

