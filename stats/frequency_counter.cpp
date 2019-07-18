#include <stats/frequency_counter.hpp>
#include <fstream>
#include <cassert>

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

    std::vector<std::pair<unsigned long, unsigned long>> data_in_range;
    unsigned long total_in_range = 0;
    auto next_to_consider = this->counts.begin();

    for(unsigned long i = start; i<= end; i++)
    {
        auto range_start = i < start + range ? start : i - range;
        auto range_end = i + range > end ? end : i + range;
        assert(range_start <= range_end);

        while (next_to_consider != std::end(this->counts) && next_to_consider->first <= range_end)
        {
            data_in_range.push_back(*next_to_consider);
            total_in_range += next_to_consider->second;
            std::advance(next_to_consider, 1);
        }

        while (data_in_range.size() != 0 && data_in_range.front().first < range_start)
        {
            total_in_range -= data_in_range.front().second;
            data_in_range.erase(data_in_range.begin());
        }

        double avg = total_in_range / (1.0 * (1 + range_end - range_start));
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
    ss << "     " << avg << " title 'moving average' with line axis x1y2\n";
}

void
frequency_counter::summarize(std::ostream& os)
{
    double mean = (1.0 * this->total) / (1.0 * this->current_time);

    os << this->name << " mean rate " << mean << " total count " << total << "\n";
}
