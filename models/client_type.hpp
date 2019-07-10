#include <models/location_model.hpp>
#include <models/client_model.hpp>


namespace ksim
{
    class client_type
    {
    public:
        virtual client_model::client_work_model generate(location_model::location_t loc) = 0;
        virtual ~client_type() = default;

    protected:
        ksim::random rand;
    };

}