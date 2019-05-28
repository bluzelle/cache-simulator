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

        actor_id_t register_actor(simulated_actor* registrant);

        void send(long send_time, actor_id_t sender, actor_id_t target, const message_t& message);

        void run_until(long time);

    private:
        void ensure_actors_set_exists(long time);

        const latency_model& latency;

        std::shared_mutex pending_actors_lock;
        std::map<long, std::pair<std::set<actor_id_t>, std::mutex>> actors_with_pending_messages;

        actor_id_t next_id;
        std::map<actor_id_t, simulated_actor*> id_map;
    };
}
