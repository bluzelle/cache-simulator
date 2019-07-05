#include <models/location_model.hpp>
#include <models/client_model.hpp>


namespace ksim
{
    class client_type
    {
        client_model::client_work_model generate(location_model::location_t loc);
    };

}