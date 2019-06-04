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

