#pragma once

#include <stats/statistic.hpp>
#include <map>

namespace ksim
{
    // Given some variable that takes string values, how many times do we see each value?
    class set_frequency_counter : public statistic
    {
    public:
        set_frequency_counter(const std::string& name) : statistic(name){}

        void finalize() override;

        void record(const std::string& value, unsigned long amount = 1);

        bool generates_graph() override {return false;}

    private:

        std::map<std::string, unsigned long> counts;
    };
}

