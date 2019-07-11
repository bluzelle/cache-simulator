#pragma once

#include <stats/statistic.hpp>
#include <vector>
#include <map>
#include <memory>

namespace ksim
{
    class statistic_set
    {
    public:
        template <class T>
        T& stat(const std::string& name)
        {
            if(this->stats.count(name) == 0)
            {
                this->stats.insert(std::make_pair(name, std::make_unique<T>(name)));
                this->stats.at(name)->update_time(this->time);
            }

            return *dynamic_cast<T*>(this->stats.at(name).get());
        }

        void update_time(unsigned long new_time);

        void finalize();

    private:
        std::map<std::string, std::unique_ptr<statistic>> stats;
        unsigned long time = 0;
    };
}

