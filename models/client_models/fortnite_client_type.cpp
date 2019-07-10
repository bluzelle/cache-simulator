#include <models/client_models/fortnite_client_type.hpp>

using namespace ksim;

fortnite_client_type::fortnite_client_type(const ksim::location_model& location_model)
    : regions(location_model, 3, 3)
{}

client_model::client_work_model fortnite_client_type::generate(ksim::location_model::location_t loc)
{
    auto key = this->regions.region_key(loc);
    client_model::client_work_model work;

    if (this->rand.next_int_inclusive(0, 1) == 0)
    {
        if (this->global_chunks.count(key) == 0)
        {
            this->global_chunks[key] = this->rand.next_string(20);
            this->global_chunks[key] += " [fortnite region chunk for " + region_model::to_string(key) + "]";
        }

        work.chunk = this->global_chunks.at(key);
        work.name = "fortnite client for region chunk";
        return work;
    }

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
