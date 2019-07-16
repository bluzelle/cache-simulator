#include <stats/frequency_counter.hpp>

using namespace ksim;

void
frequency_counter::tick()
{
    this->record(1);
}

void
frequency_counter::record(unsigned long amount)
{
    this->total += amount;
    if(this->counts.count(this->time) == 0)
    {
        this->counts[this->time] = 0;
    }

    this->counts[this->time] += amount;
}

void
frequency_counter::finalize()
{
    for (const auto& pair : this->counts)
    {
        auto time = pair.first;
        auto amount = pair.second;
        this->average_counts[time] += amount;
    }

    for (const auto& pair : this->average_counts)
    {
        this->average_counts[pair.first] = pair.second / this->average_interval;
    }
}

void
frequency_counter::report(const std::experimental::filesystem::path&)
{
    // need to add functions that conveniently yield graph/script/data file paths to statistic
}

void
frequency_counter::summarize(std::ostream& os)
{
    long mean = (1.0 * this->total) / (1.0 * this->time);
    long last = this->counts.end()->second;

    os << this->name << " mean value " << mean << " final value " << last;
}
