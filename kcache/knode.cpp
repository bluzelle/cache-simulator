#include <kcache/knode.hpp>
#include <actors/simulated_actor.hpp>

using namespace ksim::kcache;

knode::knode(actor_system& system) : simulated_actor(system)
{
}

void knode::handle_message(const ksim::message_t& /*msg*/)
{

}

void knode::start()
{

}