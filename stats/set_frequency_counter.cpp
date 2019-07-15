#include <stats/set_frequency_counter.hpp>
#include <vector>
#include <algorithm>
#include <iostream>

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
            [](const auto& pair){return pair.first;});

    std::sort(values.begin(), values.end(),
            [&](const auto& v1, const auto& v2)
            {
                return this->counts.at(v1) > this->counts.at(v2);
            });

    std::cout << this->name << " top 10: \n";
    for(unsigned int i=0; i<10 && i<values.size(); i++)
    {
        std::cout << "  " << this->counts.at(values.at(i)) << " " << values.at(i) << "\n";
    }

    // Now emit them all to the "real" output
}

