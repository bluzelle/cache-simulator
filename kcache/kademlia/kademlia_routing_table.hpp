#pragma once
#include <kcache/kademlia/kademlia_types.hpp>
#include <include/types.hpp>
#include <list>
#include <map>
#include <set>
#include <random/random.hpp>
#include <log/log.hpp>
#include <stats/statistic_set.hpp>

namespace ksim::kcache
{
    class kademlia_routing_table
    {
    public:
        using peer_record_t = std::pair<node_id_t, ksim::actor_id_t>;

        kademlia_routing_table(node_id_t id, unsigned int bucket_size, ksim::log* log_parent, ksim::statistic_set& stats);

        void insert(node_id_t kid, ksim::actor_id_t, unsigned int latency);
        bool contains(node_id_t kid, ksim::actor_id_t id) const;

        std::list<peer_record_t> k_nearest(node_id_t target) const;
        std::list<peer_record_t> random() const;

        std::set<peer_record_t> peers_closer_than(unsigned int latency) const;

        std::string to_s() const;

        unsigned int size() const;

        void finalize();

    private:

        std::set<peer_record_t> peers;

        using bucket_t = std::set<std::pair<unsigned int, peer_record_t>>; // ordered by latency
        std::map<unsigned int, bucket_t> buckets;

        ksim::random rand;
        node_id_t my_id;
        unsigned int bucket_size;

        ksim::log log;
        ksim::statistic_set& stats;
    };

}

