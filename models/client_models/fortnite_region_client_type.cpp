#include <models/client_models/fortnite_region_client_type.hpp>

using namespace ksim;

fortnite_region_client_type::fortnite_region_client_type(const ksim::location_model& location_model, const Json::Value& spec)
    : regions(location_model, spec["regions_x"].asUInt(), spec["regions_y"].asUInt())
{}

client_work_spec fortnite_region_client_type::generate(ksim::location_model::location_t loc)
{
    auto key = this->regions.region_key(loc);
    client_work_spec work;

    if (this->global_chunks.count(key) == 0)
    {
        this->global_chunks[key] = this->rand.next_string(20);
        this->global_chunks[key] += " [fortnite region chunk for " + region_model::to_string(key) + "]";
    }

    work.chunk = this->global_chunks.at(key);
    work.name = "fortnite client for region chunk";
    return work;
}
