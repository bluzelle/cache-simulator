#pragma once
#include <models/client_models/matchmaking_lobby_client_type.hpp>

using namespace ksim;

matchmaking_lobby_client_type::matchmaking_lobby_client_type(const location_model& loc)
    : regions(loc, this->x_cells, this->y_cells)
{}

client_model::client_work_model matchmaking_lobby_client_type::generate(ksim::location_model::location_t loc)
{
    auto my_key = this->regions.region_key(loc);
    auto dx = this->rand.next_int_inclusive(-this->x_range, this->x_range);
    auto dy = this->rand.next_int_inclusive(-this->y_range, this->y_range);

    auto target_key = this->regions.clip(my_key.first + dx, my_key.second + dx);

    if (this->chunks.count(target_key) == 0)
    {
        this->chunks[target_key] = this->rand.next_string(20);
        this->chunks[target_key] += "[matchmaking data chunk for " + region_model::to_string(target_key) + "]";
    }

    client_model::client_work_model work;
    work.chunk = this->chunks.at(target_key);
    work.name = "matchmaking client";

    return work;
}
