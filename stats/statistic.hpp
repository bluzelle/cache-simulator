#pragma once

namespace ksim
{
    class statistic
    {
    public:
        virtual void finalize(){};
        virtual ~statistic() = default;
    };
}
