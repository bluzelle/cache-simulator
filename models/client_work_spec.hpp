#pragma once
#include <include/types.hpp>
#include <string>

namespace ksim
{
    class client_work_spec
    {
    public:
        chunk_id_t chunk;
        double requests_per_unit_time = 0.01;
        std::string name = "";
    };
}

