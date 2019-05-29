#include <kcache/knode.hpp>
#include <actors/simulated_actor.hpp>
#include <iostream>

using namespace ksim::kcache;

knode::knode(actor_system& system, kademlia_global_state& global) : simulated_actor(system)
{
    auto intr = global.introduce(this->id);
    this->k_id = intr.first;
    this->introduction_points = intr.second;
}

void knode::handle_message(const ksim::message_t& /*msg*/)
{
    // Two RPCS- find-nearby and ping
    // find-nearby: ingest sender and give me the r k-closest node
    // ping: respond with time

    // at startup, find-nearby(my address) at all the introducer nodes

    // every second, pick a node at random from the routing table and find-nearby(my address) at it
    // on find-nearby-response, ingest every node in response
    // on ping-response, insert into routing table if appropriate

    // ingest: if it's not already in my rounting table, send it a ping

    // optionally: to accelerate the process of building the initial table, do some kind of special
    // case shortly after startup. But also that probably isn't necessary...

}

void knode::start()
{
    std::cout << "node " << this->k_id << " starting\n";
}