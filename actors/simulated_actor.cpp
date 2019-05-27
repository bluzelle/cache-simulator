#include <actors/simulated_actor.hpp>
#include <assert.h>

using namespace ksim;

void
simulated_actor::recieve_message_at(int time, const message_t& msg)
{
    assert(time > this->last_processed_time);

    this->ensure_message_set_exists(time);

    std::shared_lock<std::shared_mutex> lock(this->pending_messages_lock);
    std::lock_guard<std::mutex> lock2(this->pending_messages.at(time).second);

    this->pending_messages.at(time).first.push_back(msg);
}

void
simulated_actor::ensure_message_set_exists(int time)
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
    target->recieve_message_at(this->last_processed_time + 2 /*TODO*/, msg);
}

void
simulated_actor::process_messages_at(int time)
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
