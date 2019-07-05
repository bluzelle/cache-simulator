#include <kcache/kademlia/kademlia_routing_table.hpp>
#include <algorithm>
#include <vector>

using namespace ksim::kcache;

kademlia_routing_table::kademlia_routing_table(ksim::kcache::node_id_t id, unsigned int bucket_size, ksim::log* log_parent)
    : my_id(id)
    , bucket_size(bucket_size)
    , log("peers", log_parent)
{
}

void kademlia_routing_table::insert(ksim::kcache::node_id_t kid, ksim::actor_id_t id, unsigned int latency)
{
    this->log << "inserting " << kid << " at " << latency << "rtt \n";
    peer_record_t peer = std::make_pair(kid, id);

    if (kid == this->my_id || this->peers.count(peer) > 0)
    {
        return;
    }

    unsigned long long dist = this->my_id ^ kid; // Kademlia distance metric
    auto bucket = __builtin_clzll(dist); // equiv to "auto bucket = (8*sizeof(node_id_t)) - floor(log2(dist));"

    this->buckets[bucket].emplace(latency, peer);
    this->peers.emplace(peer);

    if (this->buckets[bucket].size() > this->bucket_size)
    {
        this->peers.erase((*(this->buckets[bucket].rbegin())).second);

        auto r = (*(this->buckets[bucket].rbegin()));
        this->log << "removing " << r.second.first << " at " << r.first << "rtt \n";

        this->buckets[bucket].erase(*(this->buckets[bucket].rbegin()));
    }
}

std::list<kademlia_routing_table::peer_record_t> kademlia_routing_table::k_nearest(ksim::kcache::node_id_t target) const
{
    if(this->peers.size() <= this->bucket_size)
    {
        std::list<peer_record_t> result(this->peers.begin(), this->peers.end());
        return result;
    }

    std::vector<peer_record_t> peers_list(this->peers.begin(), this->peers.end());

    auto ctor = [target](const peer_record_t& a, const peer_record_t& b)
    {
        return (target ^ a.first) < (target ^ b.first);
    };

    // sort the list just enough that the first r elements are the k-closest r elements in the list
    std::nth_element(peers_list.begin(), peers_list.begin() + (this->bucket_size - 1), peers_list.end(), ctor);

    std::list<peer_record_t> result(peers_list.begin(), peers_list.begin() + (this->bucket_size - 1));
    return result;
}

std::list<kademlia_routing_table::peer_record_t> kademlia_routing_table::random() const
{
    if(this->peers.size() <= this->bucket_size)
    {
        std::list<peer_record_t> result(this->peers.begin(), this->peers.end());
        return result;
    }

    std::vector<std::pair<unsigned int, peer_record_t>> peers_list;
    for (const auto peer : this->peers)
    {
        peers_list.emplace_back(this->rand.next_uint(), peer);
    }
    std::nth_element(peers_list.begin(), peers_list.begin() + (this->bucket_size - 1), peers_list.end());

    std::list<peer_record_t> result;
    for (unsigned int i = 0; i < this->bucket_size; i++)
    {
        result.emplace_back(peers_list.at(i).second);
    }

    return result;
}

bool kademlia_routing_table::contains(ksim::kcache::node_id_t kid, ksim::actor_id_t id) const
{
    return this->peers.count(std::make_pair(kid, id)) != 0;
}

std::string kademlia_routing_table::to_s() const
{
    std::string result;
    result += "Routing table for node ";
    result += std::to_string(this->my_id);
    result += "\n";

    for (const auto& pair : this->buckets)
    {
        result += " bucket ";
        result += std::to_string(pair.first);
        result += "\n";

        for (const auto& ref : pair.second)
        {
            result += "  peer ";
            result += std::to_string(ref.second.first);
            result += " at distance ";
            result += std::to_string(ref.first);
            result += "\n";
        }
    }

    return result;
}

unsigned int
kademlia_routing_table::size() const
{
    unsigned int total = 0;
    for (const auto& pair : this->buckets)
    {
        total += pair.second.size();
    }

    return total;
}

std::set<kademlia_routing_table::peer_record_t> kademlia_routing_table::peers_closer_than(unsigned int latency) const
{
    std::set<peer_record_t> result_set;

    for (const auto& bucket : this->buckets)
    {
        for (const auto &bucket_entry : bucket.second)
        {
            if (bucket_entry.first < latency)
            {
                result_set.insert(bucket_entry.second);
            }
        }
    }

    return result_set;
}

