#include <models/client_model.hpp>

using namespace ksim;

client_model::client_work_model
client_model::get_workload(const ksim::location_model::location_t /*location*/)
{
    std::string chunk;
    if(this->existing_chunks.size() < this->min_chunks || this->rand.next_unit_random() < this->new_chunk_chance)
    {
        chunk = this->rand.next_string(20);
        this->existing_chunks.push_back(chunk);
    }
    else
    {
        unsigned int len = this->existing_chunks.size();
        auto index = this->rand.next_int_inclusive(0u, len - 1);
        chunk = this->existing_chunks.at(index);
    }

    client_work_model result;
    result.chunk = chunk;

    return result;
}