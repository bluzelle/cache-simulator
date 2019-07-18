#include <models/client_model.hpp>
#include <models/client_models/eve_client_type.hpp>
#include <models/client_models/fortnite_client_type.hpp>
#include <models/client_models/matchmaking_lobby_client_type.hpp>
#include <models/client_models/random_client_type.hpp>
#include <models/client_models/weather_client_type.hpp>

using namespace ksim;

client_model::client_model(const location_model& location_model)
{
    this->types.push_back(std::make_pair(std::make_shared<eve_client_type>(), 5));
    this->types.push_back(std::make_pair(std::make_shared<fortnite_client_type>(location_model), 20));
    this->types.push_back(std::make_pair(std::make_shared<matchmaking_lobby_client_type>(location_model), 5));
    this->types.push_back(std::make_pair(std::make_shared<random_client_type>(), 20));
    this->types.push_back(std::make_pair(std::make_shared<weather_client_type>(location_model), 20));
}

client_work_spec
client_model::get_workload(const ksim::location_model::location_t location)
{
    unsigned int total_weight = 0;
    for (const auto& pair: this->types)
    {
        total_weight += pair.second;
    }

    auto choice_weight = this->rand.next_int_inclusive(0u, total_weight - 1);
    for (const auto& pair: this->types)
    {
        if (choice_weight < pair.second)
        {
            auto work = pair.first->generate(location);
            work.requests_per_unit_time *= this->rand.next_float_inclusive_exclusive(1.0, 2.0);
            return work;
        }

        choice_weight -= pair.second;
    }

    throw std::runtime_error("should not reach here");
}
