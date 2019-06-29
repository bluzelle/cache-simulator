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
        T next_int_inclusive(T lower, T upper) const
        {
            auto dist = std::uniform_int_distribution<T>(lower, upper);
            return dist(this->inner);
        }

        template <typename T>
        T next_float_inclusive_exclusive(T lower, T upper) const
        {
            auto dist = std::uniform_real_distribution<T>(lower, upper);
            return dist(this->inner);
        }

        unsigned long long next_ull() const;

        unsigned int next_uint() const;

        double next_unit_random() const;

        std::string next_string(unsigned int length) const;

    private:
        static std::atomic<unsigned int> init_count;

        mutable std::mt19937 inner;
    };
}
