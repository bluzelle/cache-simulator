#include <kcache/kcache_global_state.hpp>
#include <ctime>
#include <climits>
#include <iostream>

using namespace ksim::kcache;

kcache_global_state::kcache_global_state(const kcache_config& config)
        : config(config)
{
}

std::list<ksim::actor_id_t>
kcache_global_state::get_contacts()
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
kcache_global_state::register_address(ksim::actor_id_t registrant)
{
    this->known_nodes.push_back(registrant);
}

node_id_t
kcache_global_state::get_new_kid()
{
    return this->rand.next_ull();
}

node_id_t
kcache_global_state::chunk_address(ksim::chunk_id_t chunk)
{
    if (this->chunk_mappings.count(chunk) == 0)
    {
        this->chunk_mappings[chunk] = this->get_new_kid();
    }

    return this->chunk_mappings[chunk];
}

void
kcache_global_state::register_kid_for_storage(ksim::actor_id_t address, ksim::kcache::node_id_t kid)
{
    if (this->known_storage_kids.count(address) > 0)
    {
        throw std::runtime_error("duplicate storage registration");
    }

    this->known_storage_kids[address] = kid;
}

void
kcache_global_state::stop_caching(ksim::actor_id_t actor, ksim::chunk_id_t chunk)
{
    if (this->cache_locations[chunk].count(actor) == 0)
    {
        throw std::runtime_error("unregistering when not registered");
    }

    this->cache_locations[chunk].erase(actor);
}

void
kcache_global_state::start_caching(ksim::actor_id_t actor, ksim::chunk_id_t chunk)
{
    if (this->cache_locations[chunk].count(actor) != 0)
    {
        throw std::runtime_error("duplicate cache registration");
    }

    this->cache_locations[chunk].insert(actor);
}

const std::set<ksim::actor_id_t>&
kcache_global_state::find_authoratitive_stores(ksim::chunk_id_t chunk)
{
    if (this->authoratitive_store_locations[chunk].size() == 0)
    {
        std::vector<actor_id_t> potential_locations;
        std::transform(this->known_storage_kids.begin(), this->known_storage_kids.end(), std::back_inserter(potential_locations),
            [](const auto& pair){return pair.first;});

        node_id_t target_kid = this->chunk_address(chunk);

        auto start_sorted = potential_locations.begin();
        auto end_sorted = potential_locations.begin();
        std::advance(end_sorted, this->config.replication_factor);
        auto end_range = potential_locations.end();

        std::nth_element(start_sorted, end_sorted, end_range,
            [&](const auto& a, const auto& b)
            {
                node_id_t distance_a = target_kid ^ this->known_storage_kids[a];
                node_id_t distance_b = target_kid ^ this->known_storage_kids[b];
                return distance_a < distance_b;
            });

        std::set<actor_id_t> results;
        for(unsigned int i=0; i<this->config.replication_factor; i++)
        {
            results.insert(potential_locations[i]);
        }

        this->authoratitive_store_locations[chunk] = results;
    }

    return this->authoratitive_store_locations[chunk];
}

const std::set<ksim::actor_id_t>&
kcache_global_state::find_caches(ksim::chunk_id_t chunk)
{
    return this->cache_locations[chunk];
}
