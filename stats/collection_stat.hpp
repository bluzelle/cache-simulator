#pragma once

#include <vector>
#include <stats/statistic.hpp>
#include <sstream>
#include <iomanip>

namespace ksim
{

    // the sort of thing you'd want to draw a box plot of
    template <typename T>
    class collection_stat : public statistic
    {
    public:
        collection_stat(const std::string& name) : statistic(name){}

        void record(const T& t)
        {
            this->data.push_back(t);
        }

        void finalize() override
        {
            std::sort(this->data.begin(), this->data.end());
            T median = this->data[this->data.size()/2];
            T p10 = this->data[this->data.size()/10];
            T p1 = this->data[this->data.size()/100];
            T p90 = this->data[this->data.size()*9/10];
            T p99 = this->data[this->data.size()*99/100];

            T sum = std::accumulate(this->data.begin(), this->data.end(), 0);
            T mean = sum/this->data.size();

            std::ostringstream ss;
            ss << this->name << ": percentiles ["
                    << p1 << "/"
                    << p10 << "/"
                    << median << "/"
                    << p90 << "/"
                    << p99 << "]"
                    << ", mean " << std::setprecision(4) << mean << "\n";

            std::cout << ss.str();

            //for(unsigned int i = 0; i<this->data.size(); i++)
            //{
            //    std::cout << i << " " << this->data.at(i) << "\n";
            //}
        }
    private:
        std::vector<T> data;
    };
}