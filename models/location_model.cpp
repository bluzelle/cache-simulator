#include <ctime>
#include <tuple>
#include "location_model.hpp"

using namespace ksim;

location_model::location_model()
{
}

location_model::location
location_model::pick_location()
{
    return std::make_tuple(
            this->rand.next_int_inclusive(-200, 200),
            this->rand.next_int_inclusive(-200, 200),
            this->rand.next_int_inclusive(0, 100));
}
