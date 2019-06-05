#pragma once
#include <actors/simulated_actor.hpp>
#include <config/client_spec.hpp>
#include <random/random.hpp>

namespace ksim::kcache
{
    class kcache_client : public simulated_actor
    {
    public:
        kcache_client(ksim::actor_system& system, const ksim::client_spec& spec);

        void handle_message(const message_t& msg) override;

        void start() override;

    private:
        void do_request();

        ksim::random rand;
        const ksim::client_spec& spec;


    };
}