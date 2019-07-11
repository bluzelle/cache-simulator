#include <stats/statistic.hpp>

using namespace ksim;

statistic::statistic(const std::string& name)
    : name(name)
{}

statistic::update_time(unsigned long new_time)
{
    this->time = new_time;
}
