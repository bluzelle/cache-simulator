#pragma once
#include <kcache/kademlia_types.hpp>

namespace ksim::kcache
{
    class kademlia_routing_table
    {
    public:
        kademlia_routing_table(node_id_t id);

    private:
        node_id_t my_id;
    };

}

