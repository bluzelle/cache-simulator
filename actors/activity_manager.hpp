#pragma once
#include <include/types.hpp>
#include <unordered_map>

namespace ksim
{
    class activity_manager
    {
    public:

        class activity
        {
        public:
            activity(activity_manager* manager, std::optional<std::pair<actor_id_t, unsigned long>> existing_key = std::nullopt);

            virtual void start() = 0;
            virtual void handle_message(const message_t& msg) = 0;
            void send_message(actor_id_t target, const message_t& msg, unsigned long delay = 0);

            const actor_id_t owner;
            const unsigned long nonce;

            void done();

        };

        activity_manager(actor_id_t my_id, std::function<void(const message_t& msg)> overflow_handler);
        void handle_message(const message_t& msg);

        template<class T>
        void open(Types... args)
        {
            auto op = std::make_unique<T>(this, &args...);
            auto key = std::make_pair(op->owner, op->nonce);

            this->current_activities.insert(key, op);
        };

    private:
        unsigned long next_nonce = 1;
        std::unordered_map<std::pair<actor_id_t, unsigned long>, std::unique_ptr<activity>> current_activities;
    };

}
