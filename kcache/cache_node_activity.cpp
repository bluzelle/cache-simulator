#include <kcache/cache_node_activity.hpp>

using namespace ksim::kcache;

cache_node_activity::cache_node_activity(ksim::simulated_actor *owner, unsigned int id,
                                         std::shared_ptr<ksim::kcache::kcache_global_state> global)
        : activity(owner, id)
        , global(global)
{
}

bool
cache_node_activity::handles_message(const ksim::userspace_message_t &msg)
{
    return msg.payload_case() == userspace_message_t::kCacheFindingMessage;
}

void
cache_node_activity::handle_message(const ksim::userspace_message_t &msg)
{
    cache_finding_message inner;
    inner = msg.cache_finding_message();

    switch(inner.payload_case())
    {
        case cache_finding_message::kCacheRequest:
            this->chunk_desires[inner.cache_request().chunk_id()] += inner.cache_request().frequency();
            break;
        case cache_finding_message::kPing:
            this->reply_in_context(msg);
            break;
        default:
            throw std::runtime_error("empty cache finding message?");
    }
}

void
cache_node_activity::start()
{
    unsigned long delay = this->rand.next_int_inclusive(0ul, this->global->config.cache_choice_update_interval);
    this->start_timer(delay, [&](){this->tick();});
}

void
cache_node_activity::tick() {
    std::set<std::pair<double, chunk_id_t>> selection;

    // order the requested chunks by weight
    std::transform(this->chunk_desires.begin(), this->chunk_desires.end(), std::inserter(selection, selection.begin()),
                   [](const auto &pair) {
                       return std::make_pair(pair.second, pair.first);
                   });

    // remove the ones at the front (least) if we have too many
    if (selection.size() > this->global->config.cache_chunks_per_node) {
        auto to_remove = this->global->config.cache_chunks_per_node - selection.size();

        auto end = selection.begin();
        std::advance(end, to_remove);

        selection.erase(selection.begin(), end);
    }

    std::set<chunk_id_t> new_chunks;
    std::transform(selection.begin(), selection.end(), std::inserter(new_chunks, new_chunks.begin()),
                   [](const auto &pair) {return pair.second;});

    // identify the chunks that have been added and removed
    std::set<chunk_id_t> added;
    std::set<chunk_id_t> removed;

    std::set_difference(new_chunks.begin(), new_chunks.end(), this->current_cached_chunks.begin(),
                        this->current_cached_chunks.end(), std::inserter(added, added.begin()));
    std::set_difference(this->current_cached_chunks.begin(), this->current_cached_chunks.end(), new_chunks.begin(),
                        new_chunks.end(), std::inserter(removed, removed.begin()));

    for (const auto &chunk : added)
    {
        this->global->start_caching(this->address(), chunk);
    }

    for (const auto &chunk : removed)
    {
        this->global->stop_caching(this->address(), chunk);
    }

    this->current_cached_chunks = new_chunks;

    this->start_timer(this->global->config.cache_choice_update_interval, [&](){this->tick();});
}
