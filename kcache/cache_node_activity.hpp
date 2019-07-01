#pragma once
#include <actors/activity.hpp>
#include <include/types.hpp>
#include <kcache/kcache_global_state.hpp>
#include <random/random.hpp>

namespace ksim::kcache
{
    class cache_node_activity : public activity
    {
    public:
        cache_node_activity(simulated_actor* owner, unsigned int id, std::shared_ptr<kcache_global_state> global);

        void start() override;
        void handle_message(const userspace_message_t& msg) override;
        bool handles_message(const userspace_message_t& msg) override;

    private:
        void tick();

        std::set<ksim::chunk_id_t> current_cached_chunks;
        std::map<ksim::chunk_id_t, double> chunk_desires;

        std::shared_ptr<kcache_global_state> global;
        ksim::random rand;

    };


}
