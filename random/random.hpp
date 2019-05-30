#pragma once
#include <random>
#include <atomic>

namespace ksim
{
    class random
    {
    public:
        random();

        template <typename T>
        T next_int_inclusive(T lower, T upper)
        {
            auto dist = std::uniform_int_distribution<T>(lower, upper);
            return dist(this->inner);
        }

        unsigned long long next_ull();

        unsigned int next_uint();

    private:
        static std::atomic<unsigned int> init_count;

        std::mt19937 inner;
    };
}
