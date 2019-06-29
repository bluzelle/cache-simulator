#include <kcache/kademlia/kademlia_global_state.hpp>
#include <ctime>
#include <climits>
#include <iostream>

using namespace ksim::kcache;

kademlia_global_state::kademlia_global_state(const kademlia_config& config)
        : config(config)
{
}

std::list<ksim::actor_id_t>
kademlia_global_state::get_contacts()
{
    std::list<ksim::actor_id_t> points_of_contact;
    if (this->known_nodes.size() > 0)
    {
        for (unsigned int i=0; i < this->config.replication_factor; i++)
        {
            auto choice = this->rand.next_int_inclusive<unsigned int>(0u, this->known_nodes.size() - 1);
            points_of_contact.push_back(this->known_nodes.at(choice));
        }
    }

    return points_of_contact;
}

void
kademlia_global_state::register_address(ksim::actor_id_t registrant)
{
    this->known_nodes.push_back(registrant);
}

node_id_t
kademlia_global_state::get_new_kid()
{
    return this->rand.next_ull();
}

node_id_t
kademlia_global_state::chunk_address(ksim::chunk_id_t chunk)
{
    if (this->chunk_mappings.count(chunk) == 0)
    {
        this->chunk_mappings[chunk] = this->get_new_kid();
    }

    return this->chunk_mappings[chunk];
}