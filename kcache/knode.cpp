#include <kcache/knode.hpp>
#include <kcache/kademlia/kademlia_activity.hpp>
#include <kcache/cache_node_activity.hpp>
#include <actors/simulated_actor.hpp>
#include <iostream>
#include <proto/kcache.pb.h>

using namespace ksim::kcache;

knode::knode(actor_system& system, std::shared_ptr<kcache_global_state> global)
        : simulated_actor(system)
        , global(global)
{
}

void knode::start()
{
    auto kademlia = this->start_activity<kademlia_activity>(this->global, true);
    this->global->register_kid_for_storage(this->id, kademlia->get_k_id());
    this->start_activity<cache_node_activity>(this->global);
    this->log << "knode starting\n";
    this->log << "my location is " << std::to_string(std::get<0>(this->location)) << ", " << std::to_string(std::get<1>(this->location)) << ", " << std::to_string(std::get<2>(this->location)) << "\n";
    this->log << "my kid is " << std::to_string(kademlia->get_k_id()) << "\n";

}

