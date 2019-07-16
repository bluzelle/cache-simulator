#include <stats/set_frequency_counter.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace ksim;

void
set_frequency_counter::record(const std::string& value, unsigned long amount)
{
    this->counts[value] += amount;
}

void
set_frequency_counter::finalize()
{
    std::transform(this->counts.begin(), this->counts.end(), std::back_inserter(this->sorted),
            [](const auto& pair){return pair.first;});

    std::sort(this->sorted.begin(), this->sorted.end(),
            [&](const auto& v1, const auto& v2)
            {
                return this->counts.at(v1) > this->counts.at(v2);
            });

}

void
set_frequency_counter::report(const std::experimental::filesystem::path& dir)
{
    auto data_path = dir / std::experimental::filesystem::path("data.txt");
    std::ofstream fs(data_path);

    for(const auto& item : this->sorted)
    {
        fs << "  " << this->counts.at(item) << " " << item << "\n";
    }
}

void
set_frequency_counter::summarize(std::ostream& str)
{
    str << this->name << " top 10: \n";
    for(unsigned int i=0; i<10 && i<this->sorted.size(); i++)
    {
        str << "  " << this->counts.at(this->sorted.at(i)) << " " << this->sorted.at(i) << "\n";
    }
}