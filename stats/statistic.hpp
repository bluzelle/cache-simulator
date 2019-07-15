#pragma once
#include <string>
#include <stdexcept>
#include <iostream>
#include <experimental/filesystem>

namespace ksim
{
    class statistic
    {
    public:
        statistic(const std::string& name);

        // notably we do not implement something like record(T t) here

        virtual void finalize(){throw std::runtime_error("not implemented");};
        virtual ~statistic() = default;

        virtual void summarize(std::ostream& /*strm*/){};
        virtual void report(const std::experimental::filesystem::path& /*dir*/){};

        virtual bool generates_graph() = 0;

        void update_time(unsigned long new_time);

    protected:
        std::string name;
        unsigned long current_time = 0;
    };
}
