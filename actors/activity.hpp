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
        virtual void handle_message(const message_t& msg) = 0;
        virtual bool handles_message(const message_t& msg);

        void send_message(actor_id_t target, const message_t& msg, unsigned long delay = 0);

        void done();

    private:
        simulated_actor* owner;
        unsigned int id;
    };
}

