#pragma once

#include <models/client_type.hpp>
#include <include/types.hpp>

namespace ksim
{
    class random_client_type : public client_type
    {
        virtual client_model::client_work_model generate(location_model::location_t loc) override;

    private:
        unsigned int total_chunks = 30;
        std::map<unsigned int, chunk_id_t> chunks;
    };
}

