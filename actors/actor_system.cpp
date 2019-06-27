#include <actors/actor_system.hpp>
#include <iostream>
#include <random/random.hpp>

using namespace ksim;

actor_system::actor_system(const latency_model& latency, const location_model& location)
        : latency(latency)
        , location(location)
{}

void
actor_system::send(long send_time, actor_id_t sender, actor_id_t target, const ksim::simulator_message_t& message)
{
    long dest_time = send_time + this->latency.latency(*(this->id_map.at(sender)), *(this->id_map.at(target)));
    this->id_map.at(target)->recieve_message_at(dest_time, message);

    this->ensure_actors_set_exists(dest_time);
    std::shared_lock<std::shared_mutex> lock(this->pending_actors_lock);
    std::lock_guard<std::mutex> lock2(this->actors_with_pending_messages.at(dest_time).second);
    this->actors_with_pending_messages.at(dest_time).first.insert(target);
}

void
actor_system::ensure_actors_set_exists(long time)
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

void
actor_system::run_until(long time)
{
    random rand;
    long messages_processed = 0;

    while (!this->actors_with_pending_messages.empty() && this->actors_with_pending_messages.begin()->first <= time)
    {
        long next_tick = this->actors_with_pending_messages.begin()->first;
        auto to_act = this->actors_with_pending_messages.at(next_tick).first;
        this->actors_with_pending_messages.erase(next_tick);

        if(rand.next_uint() % 1000 == 0)
        {
            std::cout << "simulation at time " << next_tick << ", " << messages_processed << " messages processed\n";
        }

        for (const auto& actor : to_act)
        {
            messages_processed += this->id_map.at(actor)->process_messages_at(next_tick);
        }
    }
}

actor_id_t
actor_system::register_actor(simulated_actor* registrant)
{
    actor_id_t result = this->next_id++;
    this->id_map[result] = registrant;
    return result;
}

void
actor_system::finalize()
{
    for (const auto& pair : this->id_map)
    {
        pair.second->finalize();
    }
}