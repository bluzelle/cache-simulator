#pragma once
#include <include/types.hpp>
#include <mutex>
#include <shared_mutex>
#include <map>
#include <list>


namespace ksim
{
    class actor_system;

    class simulated_actor
    {
        // does messaging, time steps, etc
    public:
        simulated_actor(actor_system& system);

        virtual void handle_message(const ksim::message_t& msg) = 0;

        void process_messages_at(int time);
        void recieve_message_at(int time, const message_t& msg);

        virtual ~simulated_actor() = default;

    protected:
        void send(simulated_actor* target, const message_t& msg);

    private:
        void ensure_message_set_exists(int time);

        actor_system& system;

        int last_processed_time = 0;

        std::map<int, std::pair<std::list<message_t>, std::mutex>> pending_messages;
        std::shared_mutex pending_messages_lock;
    };
}