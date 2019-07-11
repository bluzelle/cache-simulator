#pragma once
#include <string>
#include <stdexcept>

namespace ksim
{
    class statistic
    {
    public:
        statistic(const std::string& name);

        // notably we do not implement something like record(T t) here

        virtual void finalize(){throw std::runtime_error("not implemented");};
        virtual ~statistic() = default;
        void update_time(unsigned long new_time);

    protected:
        std::string name;
        unsigned long current_time = 0;
    };
}
