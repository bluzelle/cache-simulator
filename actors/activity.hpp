#pragma once
#include <include/types.hpp>

namespace ksim
{
    class simulated_actor;

    class activity
    {
        friend class simulated_actor;

    public:
        activity();

        virtual void start() = 0;
        virtual void handle_message(const userspace_message_t& msg) = 0;
        virtual bool handles_message(const userspace_message_t& msg);

        void send_activity_message(actor_id_t target, const userspace_message_t& msg);
        void reply_in_context(const userspace_message_t& msg);

        void done();

    private:
        simulated_actor* owner;
        unsigned int id;
    };
}

