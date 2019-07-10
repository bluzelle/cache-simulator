#include <models/client_models/random_client_type.hpp>

using namespace ksim;

client_model::client_work_model random_client_type::generate(ksim::location_model::location_t /*loc*/)
{
    auto choice = this->rand.next_int_inclusive(0, this->total_chunks-1);
    if(this->chunks.count(choice) == 0)
    {
        this->chunks[choice] = this->rand.next_string(20);
        this->chunks[choice] += "[random client data chunk " + std::to_string(choice) + "]";
    }

    client_model::client_work_model work;
    work.name = "random client";
    work.chunk = this->chunks.at(choice);
}
