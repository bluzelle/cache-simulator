#pragma once
#include <include/types.hpp>
#include <functional>

namespace ksim
{
    class simulated_actor;

    class activity
    {
        friend class simulated_actor;

    public:
        activity(simulated_actor* owner, unsigned int id);

        virtual void start() = 0;
        virtual void handle_message(const userspace_message_t& msg) = 0;
        virtual bool handles_message(const userspace_message_t& msg);
        virtual void finalize();

    protected:
        void send_activity_message(actor_id_t target, const userspace_message_t& msg);
        void reply_in_context(const userspace_message_t& msg);

        void done();

        unsigned long current_time();
        actor_id_t address();
        void start_timer(unsigned long delay, std::function<void()> callback);

    private:
        simulated_actor* const owner;
        const unsigned int id;
    };
}

