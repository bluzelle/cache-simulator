#include <stats/statistic.hpp>

using namespace ksim;

statistic::statistic(const std::string& name)
    : name(name)
{}

void
statistic::update_time(unsigned long new_time)
{
    this->current_time = new_time;
}
