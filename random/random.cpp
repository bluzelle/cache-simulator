#include "random.hpp"
#include <ctime>
#include <climits>

using namespace ksim;

std::atomic<unsigned int> random::init_count = std::atomic<unsigned int>{0};

random::random()
{
    unsigned int time = static_cast<unsigned int>(std::time(0));
    std::seed_seq seed{time, random::init_count++};
    this->inner.seed(seed);
}

unsigned long long random::next_ull() const
{
    return this->next_int_inclusive(0ull, ULLONG_MAX);
}

unsigned int random::next_uint() const
{
    return this->next_int_inclusive(0u, UINT_MAX);
}

double random::next_unit_random() const
{
    return this->next_float_inclusive_exclusive(0.0, 1.0);
}

std::string random::next_string(unsigned int length) const
{
    std::string result = "";
    for(; length > 0; length--)
    {
        result += ('a' + this->next_int_inclusive(0, 25));
    }
    return result;
}
