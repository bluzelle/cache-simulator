#pragma once
#include <include/types.hpp>
#include <mutex>
#include <shared_mutex>
#include <map>
#include <list>
#include <models/location_model.hpp>


namespace ksim
{
    class actor_system;

    class simulated_actor
    {
        // does messaging, time steps, etc
    public:
        simulated_actor(actor_system& system);

        virtual void handle_message(const ksim::message_t& msg) = 0;

        virtual void start();

        virtual void finalize();

        void process_messages_at(long time);
        void recieve_message_at(long time, const message_t& msg);

        virtual ~simulated_actor() = default;

        const actor_id_t id;

        location_model::location location;

    protected:
        void send(actor_id_t target, const message_t& msg);
        void send_delayed(actor_id_t target, const message_t& msg, unsigned long delay);
        long current_time();

    private:
        void ensure_message_set_exists(long time);

        actor_system& system;

        long last_processed_time = 0;

        std::map<long, std::pair<std::list<message_t>, std::mutex>> pending_messages;
        std::shared_mutex pending_messages_lock;
        
    };
}
