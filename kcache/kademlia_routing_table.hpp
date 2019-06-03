#pragma once
#include <kcache/kademlia_types.hpp>
#include <include/types.hpp>
#include <list>
#include <unordered_map>
#include <set>
#include <random/random.hpp>

namespace ksim::kcache
{
    class kademlia_routing_table
    {
    public:
        using peer_record_t = std::pair<node_id_t, ksim::actor_id_t>;

        kademlia_routing_table(node_id_t id, unsigned int bucket_size);

        void insert(node_id_t kid, ksim::actor_id_t, unsigned int latency);
        bool contains(node_id_t kid, ksim::actor_id_t id);

        std::list<peer_record_t> k_nearest(node_id_t target);
        std::list<peer_record_t> random();

    private:

        std::set<peer_record_t> peers;

        using bucket_t = std::set<std::pair<unsigned int, peer_record_t>>; // ordered by latency
        std::unordered_map<unsigned int, bucket_t> buckets;

        ksim::random rand;
        node_id_t my_id;
        unsigned int bucket_size;
    };

}

