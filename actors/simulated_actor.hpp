#pragma once
#include <include/types.hpp>
#include <mutex>
#include <shared_mutex>
#include <map>
#include <list>
#include <models/location_model.hpp>
#include <functional>
#include <actors/activity.hpp>
#include <stats/stats.hpp>
#include <log/log.hpp>


namespace ksim
{
    class actor_system;

    class simulated_actor
    {
        friend class activity;

    public:
        simulated_actor(actor_system& system);

        virtual void handle_message(const ksim::userspace_message_t& msg);

        virtual void start();

        virtual void finalize();

        unsigned long process_messages_at(unsigned long time);
        void recieve_message_at(unsigned long time, const simulator_message_t& msg);

        virtual ~simulated_actor() = default;

        const actor_id_t id;

        location_model::location_t location;

    protected:
        template <class T, typename... Args>
        std::shared_ptr<T> start_activity(Args... args)
        {
            auto next_id = this->next_activity_id++;
            auto ptr = std::make_shared<T>(this, next_id, args...);

            this->running_activities[next_id] = ptr;
            this->running_activities[next_id]->start();

            return ptr;
        }

        void send(actor_id_t target, const simulator_message_t & msg, unsigned long delay = 0);
        void send(actor_id_t target, const userspace_message_t & msg, unsigned long delay = 0);

        void start_timer(unsigned long time, std::function<void()> callback);

        unsigned long current_time();

        userspace_message_t current_message;

        ksim::stats& stats();

        ksim::log log;

    private:
        void ensure_message_set_exists(unsigned long time);
        void deliver_message(const simulator_message_t& msg);
        void deliver_raw(const userspace_message_t& inner);

        simulator_message_t outer_current_message;

        actor_system& system;

        unsigned long last_processed_time = 1;

        std::map<unsigned long, std::pair<std::list<simulator_message_t>, std::mutex>> pending_messages;
        std::shared_mutex pending_messages_lock;

        unsigned int next_activity_id = 1;

        std::map<unsigned int, std::shared_ptr<activity>> running_activities;

        unsigned int next_timer_id = 1;

        std::map<unsigned int, std::function<void()>> running_timers;



    };
}
