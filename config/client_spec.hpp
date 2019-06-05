#pragma once

namespace ksim
{
    class client_spec
    {
    public:
        const unsigned int start_time_min = 100000;
        const unsigned int start_time_max = 120000;

        const unsigned int request_time_min = 200;
        const unsigned int request_time_max = 2000;
    };
}
