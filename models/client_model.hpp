#pragma once
#include <include/types.hpp>
#include <models/location_model.hpp>
#include <random/random.hpp>

namespace ksim
{
    class client_model
    {
    public:
        // there is no actual geographic correlation here

        class client_work_model
        {
        public:
            chunk_id_t chunk;
            double requests_per_unit_time = 0.01;
        };

        client_work_model get_workload(const location_model::location_t location);

    private:
        std::vector<chunk_id_t> existing_chunks;
        const double new_chunk_chance = 0.01;
        const unsigned int min_chunks = 10;

        random rand;
    };
}

