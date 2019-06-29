#include <ctime>
#include <tuple>
#include <cmath>
#include <algorithm>
#include <iostream>
#include "location_model.hpp"

using namespace ksim;

namespace
{
    const double pi = std::acos(-1);
}

location_model::location
location_model::pick_location()
{
    auto loc = this->select_location();
    this->placed_locations.push_back(loc);

    std::cout << "(" << std::get<0>(loc) << "," << std::get<1>(loc) << ")\n";

    return loc;
}

location_model::location
location_model::select_location()
{
    if(placed_locations.size() < this->min_sites
       || this->rand.next_unit_random() < this->break_chance)
    {
        return std::make_tuple(
                this->rand.next_float_inclusive_exclusive(this->xmin, this->xmax),
                this->rand.next_float_inclusive_exclusive(this->ymin, this->ymax),
                this->rand.next_float_inclusive_exclusive(this->zmin, this->zmax)
                );
    }

    unsigned int len = this->placed_locations.size();
    auto index = this->rand.next_int_inclusive(0u, len - 1);
    auto parent = this->placed_locations.at(index);

    // exponential distance from the parent node in a random direction
    auto distance = -city_radius * log(this->rand.next_unit_random());

    auto theta = this->rand.next_float_inclusive_exclusive(0.0, 2*pi);

    auto delta_x = std::sin(theta) * distance;
    auto delta_y = std::cos(theta) * distance;

    auto x = std::get<0>(parent) + delta_x;
    auto y = std::get<1>(parent) + delta_y;

    // wrap around the east and west edges of the cylinder
    while(x > this->xmax)
    {
        x -= (this->xmax - this->xmin);
    }

    while(x < this->xmin)
    {
        x += (this->xmax - this->xmin);
    }

    // clip to the north and south edges of the cylinder
    y = std::max(std::min(y, this->ymax), this->ymin);

    // chose the z offset uniformly at random
    return std::make_tuple(x, y, this->rand.next_float_inclusive_exclusive(this->zmin, this->zmax));

}
