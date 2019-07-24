#pragma once
#include <include/types.hpp>
#include <models/location_model.hpp>
#include <random/random.hpp>
#include <models/client_type.hpp>
#include <models/client_work_spec.hpp>
#include <options/options.hpp>

namespace ksim
{
    class client_type;

    class client_model
    {
    public:
        // there is no actual geographic correlation here


        client_model(const location_model& location_model, const ksim::options& opt);

        client_work_spec get_workload(const location_model::location_t location);

    private:
        std::vector<std::pair<std::shared_ptr<client_type>, unsigned int>> types;
        random rand;
    };
}

