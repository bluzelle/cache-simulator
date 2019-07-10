#include <models/client_models/region_model.hpp>

using namespace ksim;

region_model::region_model(const ksim::location_model& loc, unsigned int x_count, unsigned int y_count)
    : x_cells(x_count)
    , y_cells(y_count)
    , x_res((loc.xmax - loc.xmin)/x_count)
    , y_res((loc.ymax - loc.ymin)/y_count)
    , x_min(loc.xmin / this->x_res)
    , x_max(loc.xmax / this->x_res)
    , y_min(loc.ymin / this->y_res)
    , y_max(loc.ymax / this->y_res)
{}

region_model::key_t region_model::region_key(ksim::location_model::location_t loc) const
{
    return std::make_pair(std::get<0>(loc)/this->x_res, std::get<1>(loc)/this->y_res);
}

region_model::key_t region_model::clip(int x, int y)
{
    while (x < this->x_min)
    {
        x += (this->x_max - this->x_min);
    }

    while (x > this->x_max)
    {
        x -= (this->x_max - this->x_min);
    }

    y = std::min(y, this->y_max);
    y = std::max(y, this->y_min);

    return std::make_pair(x, y);
}

std::string region_model::to_string(ksim::region_model::key_t key)
{
    std::string result = "(";
    result += std::to_string(key.first);
    result += ",";
    result += std::to_string(key.second);
    result += ")";

    return result;
}