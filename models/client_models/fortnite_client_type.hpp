#pragma once

#include <models/client_type.hpp>
#include <models/client_models/region_model.hpp>

namespace ksim
{
    /*
     * For a game that places a small number of players together in an instance with many such instances per region;
     * eg moba games or battle royale games
     *
     * Location space is divided into large regions, each region has many session chunks and one global state chunk
     * clients are 50% interested in one session chunk at random for their region, 50% interested in the global state
     * chunk for their region
     *
     * Ideal result:
     * global chunk cached very widely, even outside pop centres
     * session chunks less commonly cached (maybe not at all if sessions are small), but if cached they are only cached
     * in population centres
     */
    class fortnite_client_type : public client_type
    {
    public:
        fortnite_client_type(const location_model& location_model);
        virtual client_work_spec generate(location_model::location_t loc) override;

    private:
        const region_model regions;

        const unsigned int clients_per_session = 50;

        std::map<region_model::key_t, chunk_id_t> global_chunks;

        std::map<region_model::key_t, chunk_id_t> sessions_building;
        std::map<region_model::key_t, unsigned int> slots_remaining;
        std::map<region_model::key_t, unsigned int> sessions_built;
    };
}
