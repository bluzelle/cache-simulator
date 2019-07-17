#include <kcache/kclient.hpp>
#include <kcache/cache_client_activity.hpp>
#include <kcache/kademlia/kademlia_activity.hpp>
#include <stats/xy_plot_statistic.hpp>

using namespace ksim::kcache;
kclient::kclient(ksim::actor_system &system, std::shared_ptr<ksim::kcache::kcache_global_state> global, client_model& model)
        : simulated_actor(system)
        , global(global)
        , work(model.get_workload(this->location))
        , k_id(global->chunk_address(this->work.chunk))
{
    this->stats().stat<xy_plot_statistic>("client geographic distribution").record(std::get<0>(this->location), std::get<1>(this->location));
    this->stats().stat<xy_plot_statistic>(this->work.name + " client geographic distribution").record(std::get<0>(this->location), std::get<1>(this->location));
}

void
kclient::start()
{
    auto kademlia = this->start_activity<kademlia_activity>(this->global, false, this->k_id);
    this->start_activity<cache_client_activity>(this->global, kademlia, this->work);
}
