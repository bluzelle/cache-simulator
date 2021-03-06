#pragma once

#include <models/client_type.hpp>
#include <include/types.hpp>

namespace ksim
{
    class random_client_type : public client_type
    {
        virtual client_work_spec generate(location_model::location_t loc) override;

    private:
        unsigned int total_chunks = 50;
        std::map<unsigned int, chunk_id_t> chunks;
    };
}

