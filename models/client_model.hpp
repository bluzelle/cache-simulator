#pragma once
#include <include/types.hpp>
#include <models/location_model.hpp>
#include <random/random.hpp>
#include <models/client_type.hpp>

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
            std::string name = "";
        };

        client_model(const location_model& location_model);

        client_work_model get_workload(const location_model::location_t location);

    private:
        std::vector<std::pair<std::unique_ptr<client_type>, unsigned int>> types;
        random rand;
    };
}

