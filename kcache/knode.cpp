#include <kcache/knode.hpp>
#include <actors/simulated_actor.hpp>
#include <iostream>

using namespace ksim::kcache;

knode::knode(actor_system& system, kademlia_global_state& global) : simulated_actor(system)
{
    auto intr = global.introduce(this);
    this->id = intr.first;
    this->introduction_points = intr.second;
}

void knode::handle_message(const ksim::message_t& /*msg*/)
{

}

void knode::start()
{
    std::cout << "node " << this->id << " starting\n";
}