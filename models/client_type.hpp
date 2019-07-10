#pragma once

#include <models/location_model.hpp>
#include <models/client_model.hpp>
#include <models/client_work_spec.hpp>

namespace ksim
{
    class client_type
    {
    public:
        virtual client_work_spec generate(location_model::location_t loc) = 0;
        virtual ~client_type() = default;

    protected:
        ksim::random rand;
    };

}