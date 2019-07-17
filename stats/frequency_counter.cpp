#include <stats/frequency_counter.hpp>
#include <fstream>

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
    this->counts[this->current_time] += amount;
}

void
frequency_counter::finalize()
{
    auto range = this->average_interval / 2;
    auto start = this->counts.begin()->first;
    auto end = this->counts.rbegin()->first;

    for(unsigned long i = start; i <= end; i++)
    {
        auto range_start = i < start + range ? start : i - range;
        auto range_end = i + range > end ? end : i + range;

        long sum = 0;

        for(unsigned long j = range_start; j <= range_end; j++)
        {
            sum += this->counts[j];
        }

        double avg = sum / (1.0 * (1+range_end - range_start));
        this->average_counts[i] = avg;
    }
}

void
frequency_counter::report()
{
    auto raw = this->data_path("raw");
    auto avg = this->data_path("moving_average");

    std::ofstream rawf(raw);
    std::ofstream avgf(avg);

    for (const auto& pair : this->counts)
    {
        rawf << pair.first << " " << pair.second << "\n";
    }

    for (const auto& pair : this->average_counts)
    {
        avgf << pair.first << " " << pair.second << "\n";
    }

    this->write_common_script_prefix();
    std::ofstream ss(this->script_path(), std::ios::app);

    ss << "plot " << raw << " title 'raw frequency' with points, \\\n";
    ss << "     " << avg << " title 'moving average' with points\n";
}

void
frequency_counter::summarize(std::ostream& os)
{
    double mean = (1.0 * this->total) / (1.0 * this->current_time);
    long last = this->counts.end()->second;

    os << this->name << " mean rate " << mean << " final rate " << last << "\n";
}
