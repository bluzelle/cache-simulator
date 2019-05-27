#pragma once
#include <include/types.hpp>
#include <actors/simulated_actor.hpp>
#include <set>

namespace ksim
{
    class actor_system
    {
    public:
        void send(simulated_actor* target, const message_t& message);

    private:
        std::map<int, std::pair<std::set<simulated_actor*>, std::mutex>> actors_with_pending_messages;
    };
}
