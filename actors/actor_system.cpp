#include <actors/actor_system.hpp>
#include <iostream>
#include <random/random.hpp>
#include <csignal>
#include <stats/frequency_counter.hpp>

using namespace ksim;

actor_system::actor_system(const latency_model& latency, location_model& location, ksim::statistic_set& stats, log_base& log_parent)
        : latency(latency)
        , location(location)
        , stats(stats)
        , log("actorsys", log_parent)
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

    this->stats.stat<frequency_counter>("messages sent").tick();
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

bool canceled = false;
void cancel(int /*signum*/)
{
    canceled = true;
}

void
actor_system::run_until(long time)
{
    random rand;
    unsigned long messages_processed = 0;

    signal(SIGINT, cancel);

    while (!canceled && !this->actors_with_pending_messages.empty() && this->actors_with_pending_messages.begin()->first <= time)
    {
        long next_tick = this->actors_with_pending_messages.begin()->first;
        this->log.set_prefix("actorsys t" + std::to_string(next_tick));
        this->stats.update_time(next_tick);
        auto to_act = this->actors_with_pending_messages.at(next_tick).first;
        this->actors_with_pending_messages.erase(next_tick);

        for (const auto& actor : to_act)
        {
            auto delta = this->id_map.at(actor)->process_messages_at(next_tick);
            if (messages_processed / 100000 != (messages_processed+delta) / 100000)
            {
                this->log << messages_processed+delta << " total messages processed\n";
            }
            messages_processed += delta;
            this->stats.stat<frequency_counter>("messages delivered").record(delta);
        }
    }

    if(canceled)
    {
        this->log << "quitting early in response to keyboard interrupt";
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
