#pragma once
#include <include/types.hpp>
#include <mutex>
#include <shared_mutex>
#include <map>
#include <list>

namespace ksim
{
    class simulated_actor
    {
        // does messaging, time steps, etc
    public:
        virtual void handle_message(const ksim::message_t& msg);

        void process_messages_at(int time);
        void recieve_message_at(int time, const message_t& msg);

    protected:
        void send(simulated_actor* target, const message_t& msg);

    private:
        void ensure_message_set_exists(int time);

        int last_processed_time = 0;

        std::map<int, std::pair<std::list<message_t>, std::mutex>> pending_messages;
        std::shared_mutex pending_messages_lock;
    };
}
