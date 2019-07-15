#include <kcache/cache_node_activity.hpp>
#include <stats/set_frequency_counter.hpp>
#include <stats/collection_stat.hpp>

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
    this->log.say("cache node starting");
    unsigned long delay = this->rand.next_int_inclusive(0ul, this->global->config.cache_choice_update_interval);
    this->start_timer(delay, [&](){this->tick();});
}

void
cache_node_activity::tick() {
    this->log.say("tick");
    std::set<std::pair<double, chunk_id_t>> selection;

    // order the requested chunks by weight
    std::transform(this->chunk_desires.begin(), this->chunk_desires.end(), std::inserter(selection, selection.begin()),
                   [](const auto &pair) {
                       return std::make_pair(pair.second, pair.first);
                   });

    for (const auto& pair: selection)
    {
        this->log << "chunk " << pair.second << " requested with weight " << pair.first << "\n";
    }

    // remove the ones at the front (least) if we have too many
    while(selection.size() > this->global->config.cache_chunks_per_node) {
        selection.erase(selection.begin());
    }

    assert(selection.size() <= this->global->config.cache_chunks_per_node);

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

    this->log << this->current_cached_chunks.size() << " chunks were cached, adding " << added.size() << " and removing " << removed.size() << "\n";
    for (const auto &chunk : added)
    {
        this->log << "starting cache of " << chunk << "\n";
        this->global->start_caching(this->address(), chunk);
    }

    for (const auto &chunk : removed)
    {
        this->log << "stopping cache of " << chunk << "\n";
        this->global->stop_caching(this->address(), chunk);
    }

    this->current_cached_chunks = new_chunks;
    this->chunk_desires.clear();

    this->log << "now " << this->current_cached_chunks.size() << " chunks are cached\n";

    this->start_timer(this->global->config.cache_choice_update_interval, [&](){this->tick();});
}

void
cache_node_activity::finalize()
{
    this->log << "cache node final cache set:\n";
    for(const auto& chunk : this->current_cached_chunks)
    {
        this->log << "  " << chunk << "\n";
        this->stats().stat<set_frequency_counter>("cached chunks").record(chunk);
        this->stats().stat<collection_stat<unsigned long>>("cache chunks per node").record(this->current_cached_chunks.size());
    }

}
