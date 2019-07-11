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
