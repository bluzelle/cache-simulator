#include <stats/statistic_set.hpp>

using namespace ksim;

void 
statistic_set::finalize()
{
    for(const auto& stat: this->stats){
        // find a directory and pass it
        stat.second->finalize();
    }
}

void
statistic_set::update_time(unsigned long new_time)
{
    this->time = new_time;
    for(const auto& stat_pair : this->stats)
    {
        stat_pair.second->update_time(new_time);
    }
}

