#pragma once

namespace ksim::kcache
{
    class kademlia_config
    {
    public:
        const unsigned int replication_factor = 3;
        const unsigned int gossip_time_min = 3000;
        const unsigned int gossip_time_max = 7000;
    };
}
