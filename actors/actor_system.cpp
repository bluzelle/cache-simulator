#include <actors/actor_system.hpp>

using namespace ksim;

actor_system::actor_system(latency_model& latency)
        : latency(latency)
{}

void
actor_system::send(int send_time, simulated_actor* sender, simulated_actor* target, const ksim::message_t& message)
{
    int dest_time = send_time + this->latency.latency(sender, target);
    target->recieve_message_at(dest_time, message);

    this->ensure_actors_set_exists(dest_time);
    std::shared_lock<std::shared_mutex> lock(this->pending_actors_lock);
    std::lock_guard<std::mutex> lock2(this->actors_with_pending_messages.at(dest_time).second);
    this->actors_with_pending_messages.at(dest_time).first.insert(target);
}

void
actor_system::ensure_actors_set_exists(int time)
{
    bool exists;
    {
        std::shared_lock<std::shared_mutex> lock(this->pending_actors_lock);
        exists = this->actors_with_pending_messages.count(time) != 0;
    }

    if (!exists)
    {
        std::lock_guard<std::shared_mutex> lock(this->pending_actors_lock);
        this->actors_with_pending_messages[time];
    }
}
