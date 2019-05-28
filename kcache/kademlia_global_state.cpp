#include <kcache/kademlia_global_state.hpp>
#include <ctime>
#include <climits>

using namespace ksim::kcache;

kademlia_global_state::kademlia_global_state(const kademlia_config& config)
        : config(config)
{
    this->rand.seed(std::time(nullptr));
}

std::pair<node_id, std::list<ksim::simulated_actor*>>
kademlia_global_state::introduce(ksim::simulated_actor* registrant)
{
    std::list<ksim::simulated_actor*> points_of_contact;
    if (this->known_nodes.size() > 0)
    {
        for (int i=0; i < this->config.replication_factor; i++)
        {
            std::uniform_int_distribution<> dist(0, this->known_nodes.size() - 1);
            points_of_contact.push_back(this->known_nodes.at(dist(this->rand)));
        }
    }

    this->known_nodes.push_back(registrant);

    auto id = std::uniform_int_distribution<unsigned long long>(0, ULLONG_MAX)(rand);
    return std::make_pair(id, points_of_contact);
}
