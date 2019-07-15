#pragma once

#include <stats/statistic.hpp>
#include <map>

namespace ksim
{
    /*
     * frequency for some event over time
     */
    class frequency_counter : public statistic
    {
    public:

        frequency_counter(const std::string& name) : statistic(name){}

        void tick();
        void record(unsigned long amount);

        void finalize() override;

        bool generates_graph() override {return false;}

    private:
        unsigned long total;
        std::map<unsigned long, unsigned long> counts;
    }
}
