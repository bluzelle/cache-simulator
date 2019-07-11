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
frequency_counter::finalize() override
{
    long mean = (1.0 * this->total) / (1.0 * this->time);

    //summary
    std::cout 
        << this->name 
        << ": total " << this->total 
        << " mean " << this->mean << " events/tick\n";

//    //graph
//    for(const auto& pair : this->counts)
//    {
//        std::cout << pair.first << " " << pair.second << "\n";
//    }
}

