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

        void summarize(std::ostream& /*strm*/);
        void report();

    private:
        unsigned long total;
        const unsigned long average_interval = 1000;
        std::map<unsigned long, unsigned long> counts;
        std::map<unsigned long, double> average_counts;
    };
}
