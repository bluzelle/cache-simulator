#include <models/client_models/eve_client_type.hpp>

using namespace ksim;

eve_client_type::eve_client_type()
    : regions(this->virtual_location_model, 10, 10)
{}

client_work_spec eve_client_type::generate(ksim::location_model::location_t /*loc*/)
{
    auto virtual_loc = this->virtual_location_model.pick_location();
    auto key = this->regions.region_key(virtual_loc);

    if(this->chunks.count(key) == 0)
    {
        this->chunks[key] = this->rand.next_string(20);
        this->chunks[key] += " [eve chunk for v";
        this->chunks[key] += this->regions.to_string(key);
        this->chunks[key] += "]";
    }

    client_work_spec work;
    work.chunk = this->chunks.at(key);
    work.name = "eve client";

    return work;
}
