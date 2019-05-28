#pragma once
#include <include/types.hpp>
#include <models/latency_model.hpp>
#include <actors/simulated_actor.hpp>
#include <set>
#include <mutex>
#include <shared_mutex>

namespace ksim
{
    class actor_system
    {
    public:
        actor_system(const latency_model& latency);
        void send(long send_time, simulated_actor* sender, simulated_actor* target, const message_t& message);

        void run_until(long time);

    private:
        void ensure_actors_set_exists(long time);

        const latency_model& latency;

        std::shared_mutex pending_actors_lock;
        std::map<long, std::pair<std::set<simulated_actor*>, std::mutex>> actors_with_pending_messages;
    };
}
