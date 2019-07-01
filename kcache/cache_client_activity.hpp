#pragma once
#include <actors/activity.hpp>
#include <models/client_model.hpp>
#include <random/random.hpp>
#include <kcache/kcache_global_state.hpp>
#include <climits>

namespace ksim::kcache
{
    class cache_client_activity : public activity {
        cache_client_activity(simulated_actor* owner, unsigned int id, std::shared_ptr<kcache_global_state> global);

        void start() override;

        void handle_message(const userspace_message_t&) override;

        void finalize() override;

    private:
        void tick();
        void maybe_ping(actor_id_t target, ping_type type);

        client_model::client_work_model work;

        std::shared_ptr<kcache_global_state> global;
        ksim::random rand;

        std::map<actor_id_t, unsigned long> known_latencies;

        unsigned long closest_authoratative_source = ULONG_MAX;
        unsigned long closest_cache = ULONG_MAX;
    };
}
