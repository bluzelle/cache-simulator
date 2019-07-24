#include <models/client_models/fortnite_session_client_type.hpp>

using namespace ksim;

fortnite_session_client_type::fortnite_session_client_type(const ksim::location_model& location_model, const Json::Value& spec)
    : regions(location_model, spec["regions_x"].asUInt(), spec["regions_y"].asUInt())
    , clients_per_session(spec["clients_per_session"].asUInt())
{}

client_work_spec fortnite_session_client_type::generate(ksim::location_model::location_t loc)
{
    auto key = this->regions.region_key(loc);
    client_work_spec work;

    if (this->slots_remaining.count(key) == 0)
    {
        this->slots_remaining[key] = 0;
    }

    if (this->slots_remaining.at(key) == 0)
    {
        this->sessions_building[key] = this->rand.next_string(20);
        this->sessions_building[key] += " [fortnite session chunk " + std::to_string(this->sessions_built[key])
                + " for " + region_model::to_string(key) + "]";
        this->slots_remaining[key] = this->clients_per_session;
        this->sessions_built[key]++;
    }

    this->slots_remaining[key]--;
    work.chunk = this->sessions_building[key];
    work.name = "fortnite client for session chunk";
    return work;
}
