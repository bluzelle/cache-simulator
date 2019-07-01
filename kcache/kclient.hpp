#pragma once
#include <actors/simulated_actor.hpp>
#include <kcache/kcache_global_state.hpp>
#include <models/client_model.hpp>

namespace ksim::kcache
{
    class kclient : public simulated_actor
    {
    public:
        kclient(ksim::actor_system& system, std::shared_ptr<kcache_global_state> global, client_model& model);

        void start() override;

    private:
        std::shared_ptr<kcache_global_state> global;
        const client_model::client_work_model work;
        node_id_t k_id;
    };
}

