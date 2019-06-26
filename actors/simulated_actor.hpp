#pragma once
#include <include/types.hpp>
#include <mutex>
#include <shared_mutex>
#include <map>
#include <list>
#include <models/location_model.hpp>
#include <functional>
#include <actors/activity.hpp>


namespace ksim
{
    class actor_system;

    class simulated_actor
    {
        friend class activity;

    public:
        simulated_actor(actor_system& system);

        virtual void handle_message(const ksim::message_t& msg);

        virtual void start();

        virtual void finalize();

        void process_messages_at(long time);
        void recieve_message_at(long time, const env_t& msg);

        virtual ~simulated_actor() = default;

        const actor_id_t id;

        location_model::location location;

    protected:
        template <class T, typename... Args>
        void start_activity(Args... args)
        {
            auto id = this->next_activity_id++;
            auto ptr = std::make_unique<T>(args...);
            ptr->owner = this;
            ptr->id = id;

            this->running_activities.insert(std::make_pair(id, ptr));
            this->running_activities[id]->start();
        }

        void send(actor_id_t target, const message_t& msg, unsigned long delay = 0);
        void send(actor_id_t target, const env_t& msg, unsigned long delay = 0);

        unsigned long current_time();

    private:
        void ensure_message_set_exists(long time);
        void deliver_message(const env_t& msg);
        void deliver_raw(const message_t& inner);

        actor_system& system;

        unsigned long last_processed_time = 0;

        std::map<long, std::pair<std::list<env_t>, std::mutex>> pending_messages;
        std::shared_mutex pending_messages_lock;

        unsigned int next_activity_id;

        std::map<unsigned int, std::unique_ptr<activity>> running_activities;

    };
}
