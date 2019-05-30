#include <kcache/kademlia_global_state.hpp>
#include <ctime>
#include <climits>
#include <iostream>

using namespace ksim::kcache;

kademlia_global_state::kademlia_global_state(const kademlia_config& config)
        : config(config)
{
}

std::pair<node_id_t, std::list<ksim::actor_id_t>>
kademlia_global_state::introduce(ksim::actor_id_t registrant)
{
    std::list<ksim::actor_id_t> points_of_contact;
    if (this->known_nodes.size() > 0)
    {
        for (int i=0; i < this->config.replication_factor; i++)
        {
            auto choice = this->rand.next_int_inclusive<unsigned int>(0u, this->known_nodes.size() - 1);
            points_of_contact.push_back(this->known_nodes.at(choice));
        }
    }

    this->known_nodes.push_back(registrant);

    return std::make_pair(this->rand.next_ull(), points_of_contact);
}
