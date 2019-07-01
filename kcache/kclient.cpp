#include <kcache/kclient.hpp>
#include <kcache/kademlia/kademlia_activity.hpp>

using namespace ksim::kcache;
kclient::kclient(ksim::actor_system &system, std::shared_ptr<ksim::kcache::kcache_global_state> global, client_model& model)
        : simulated_actor(system)
        , global(global)
        , work(model.get_workload(this->location))
        , k_id(global->chunk_address(this->work.chunk))
{

}

void
kclient::start()
{
    this->start_activity<kademlia_activity>(this->global, false, this->k_id);
}
