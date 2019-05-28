#include <actors/simulated_actor.hpp>
#include <actors/actor_system.hpp>
#include <assert.h>

using namespace ksim;

simulated_actor::simulated_actor(actor_system& system)
        : system(system)
{
}

void
simulated_actor::recieve_message_at(long time, const message_t& msg)
{
    assert(time > this->last_processed_time);

    this->ensure_message_set_exists(time);

    std::shared_lock<std::shared_mutex> lock(this->pending_messages_lock);
    std::lock_guard<std::mutex> lock2(this->pending_messages.at(time).second);

    this->pending_messages.at(time).first.push_back(msg);
}

void
simulated_actor::ensure_message_set_exists(long time)
{
    bool exists;
    {
        std::shared_lock lock(this->pending_messages_lock);
        exists = this->pending_messages.count(time) != 0;
    }

    if (!exists)
    {
        std::lock_guard<std::shared_mutex> lock(this->pending_messages_lock);
        this->pending_messages[time];
    }
}

void
simulated_actor::send(simulated_actor* target, const message_t& msg)
{
    this->system.send(this->last_processed_time, this, target, msg);
}

void
simulated_actor::process_messages_at(long time)
{
    assert(time > this->last_processed_time);
    this->last_processed_time = time;

    std::list<message_t> msgs;

    {
        std::shared_lock lock(this->pending_messages_lock);
        msgs = this->pending_messages.at(time).first;
        this->pending_messages.erase(time);
    }

    for (const auto& msg : msgs)
    {
        this->handle_message(msg);
    }
}

void
simulated_actor::start()
{

}
