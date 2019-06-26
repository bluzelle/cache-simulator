#pragma once
#include <include/types.hpp>

namespace ksim
{
    class activity
    {
    public:
        activity();

        virtual void start() = 0;
        virtual void handle_message(const message_t& msg) = 0;

        void send_message(actor_id_t target, const message_t& msg, unsigned long delay = 0);

        const actor_id_t owner;
        const unsigned long nonce;

        void done();

    };
}

