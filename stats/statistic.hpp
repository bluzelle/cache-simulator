#pragma once

namespace ksim
{
    class statistic
    {
    public:
        statistic(const std::string& name);

        template <typename T>
        virtual void record_point(T){throw std::runtime_error("unimplemented");}

        virtual void finalize(){};
        virtual ~statistic() = default;

    protected:
        std::string name;
    };
}
