#include <config/sim_config.hpp>

using namespace ksim;

sim_config::sim_config(const ksim::options& opt)
    : clients_count(opt.get()["customer_node_count"].asUInt64())
    , nodes_count(opt.get()["blz_node_count"].asUInt64())
    , duration(opt.get()["duration"].asUInt64())
    , latency()
    , clients(this->location, opt)
{}
