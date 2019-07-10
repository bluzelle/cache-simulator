#include <models/client_model.hpp>
#include <models/client_models/eve_client_type.hpp>
#include <models/client_models/fortnite_client_type.hpp>
#include <models/client_models/matchmaking_lobby_client_type.hpp>
#include <models/client_models/random_client_type.hpp>
#include <models/client_models/weather_client_type.hpp>

using namespace ksim;

client_model::client_model(const location_model& location_model)
{
    this->types.push_back(std::make_pair(std::make_unique<eve_client_type>(), 5));
    this->types.push_back(std::make_pair(std::make_unique<fortnite_client_type>(location_model), 20));
    this->types.push_back(std::make_pair(std::make_unique<matchmaking_lobby_client_type>(location_model), 10));
    this->types.push_back(std::make_pair(std::make_unique<random_client_type>(), 5));
    this->types.push_back(std::make_pair(std::make_unique<weather_client_type>(location_model), 10));
}

client_model::client_work_model
client_model::get_workload(const ksim::location_model::location_t location)
{
    unsigned int total_weight = 0;
    for (const auto& pair: this->types)
    {
        total_weight += pair.second;
    }

    int choice_weight = this->rand.next_int_inclusive(0, total_weight - 1);
    for (const auto& pair: this->types)
    {
        if (choice_weight < pair.second)
        {
            return pair.first->generate(location);
        }

        choice_weight -= pair.second;
    }

    throw std::runtime_error("should not reach here");
}
