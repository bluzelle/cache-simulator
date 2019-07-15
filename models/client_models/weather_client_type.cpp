#include <models/client_models/weather_client_type.hpp>
#include <models/client_model.hpp>

using namespace ksim;

weather_client_type::weather_client_type(const location_model& loc)
    : regions(loc, 30, 30)
{}

client_work_spec weather_client_type::generate(ksim::location_model::location_t loc)
{
    auto key = this->regions.region_key(loc);

    if(this->chunks.count(key) == 0)
    {
        this->chunks[key] = this->rand.next_string(20);
        this->chunks[key] += " [weather client for region " + region_model::to_string(key) + "]";
    }

    client_work_spec work;
    work.chunk = this->chunks.at(key);
    work.name = "weather client";

    return work;
}
