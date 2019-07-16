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
        void report(const std::experimental::filesystem::path& /*dir*/);

        bool generates_graph() override {return false;}

    private:
        unsigned long total;
        const unsigned long average_interval;
        std::map<unsigned long, unsigned long> counts;
        std::map<unsigned long, unsigned long> average_counts;
    }
}
