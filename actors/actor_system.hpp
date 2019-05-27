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
        void send(int send_time, simulated_actor* sender, simulated_actor* target, const message_t& message);

    private:
        void ensure_actors_set_exists(int time);

        latency_model latency;

        std::shared_mutex pending_actors_lock;
        std::map<int, std::pair<std::set<simulated_actor*>, std::mutex>> actors_with_pending_messages;
    };
}
