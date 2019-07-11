#pragma once

#include <stats/statistic.hpp>
#include <vector>

namespace ksim
{
    class statistic_set
    {
    public:
        template <class T>
        statistic& operator(const std::string& name)
        {
            if(this->stats.count(name) == 0)
            {
                this->stats.insert(name, std::make_unique<T>());
            }

            return this->stats.at(name);
        }

        void finalize();

    private:
        std::map<std::string, std::unique_ptr<statistic>> stats;
    };
}

