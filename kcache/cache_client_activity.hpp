#pragma once
#include <actors/activity.hpp>
#include <models/client_model.hpp>
#include <random/random.hpp>
#include <kcache/kcache_global_state.hpp>
#include <kcache/kademlia/kademlia_activity.hpp>
#include <climits>

namespace ksim::kcache
{
    class cache_client_activity : public activity {
    public:
        cache_client_activity(simulated_actor* owner, unsigned int id,
                              std::shared_ptr<kcache_global_state> global, std::shared_ptr<kademlia_activity> kademlia, const client_work_spec& work);

        void start() override;

        void handle_message(const userspace_message_t&) override;

        void finalize() override;

    private:
        void tick();
        void maybe_ping(actor_id_t target, ping_type type);
        void send_speculative_request(actor_id_t target);

        client_work_spec work;

        std::shared_ptr<kcache_global_state> global;
        std::shared_ptr<kademlia_activity> kademlia;
        ksim::random rand;

        std::map<actor_id_t, unsigned long> known_latencies;

        actor_id_t closest_authoratative_source = 0;
        unsigned long closest_authoratative_source_latency = ULONG_MAX;
        actor_id_t closest_cache = 0;
        unsigned long closest_cache_latency = ULONG_MAX;
    };
}
