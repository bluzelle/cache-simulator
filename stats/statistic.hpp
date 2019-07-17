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

        virtual ~statistic() = default;

        virtual void finalize(){};
        virtual void summarize(std::ostream& /*strm*/){};
        virtual void report(){};

        void set_path(const std::experimental::filesystem::path& path);

        std::experimental::filesystem::path graph_path();
        std::experimental::filesystem::path script_path();
        std::experimental::filesystem::path data_path(const std::string& name = "data");

        bool graph_generated();

        void update_time(unsigned long new_time);

    protected:
        void write_common_script_prefix();
        std::string name;
        unsigned long current_time = 0;

    private:
        std::experimental::filesystem::path named_path(const std::string&);

        std::experimental::filesystem::path root_path;

        bool graph_path_used = false;
    };
}
