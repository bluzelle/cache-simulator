#include <stats/set_frequency_counter.hpp>

using namespace ksim;

void
set_frequency_counter::record(const std::string& value, unsigned long amount)
{
    this->counts[value] += amount;
}

void
set_frequency_counter::finalize()
{
    std::vector<std::string> values;
    std::transform(this->counts.begin(), this->counts.end(), std::back_inserter(values), 
            [](const auto& pair){return pair.second});

    std::sort_by(values.begin(), values.end(), 
            [](const auto& v1, const auto& v2)

