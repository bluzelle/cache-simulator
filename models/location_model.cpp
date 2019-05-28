#include <ctime>
#include <tuple>
#include "location_model.hpp"

using namespace ksim;

location_model::location_model()
{
    rand.seed(std::time(nullptr));
}

location_model::location
location_model::pick_location()
{
    std::uniform_int_distribution<> xdis(-200, 200);
    std::uniform_int_distribution<> ydis(-200, 200);
    std::uniform_int_distribution<> zdis(0, 100);

    return std::make_tuple(xdis(this->rand), ydis(this->rand), zdis(this->rand));
}
