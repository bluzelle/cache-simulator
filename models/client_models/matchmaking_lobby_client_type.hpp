#pragma once
#include <models/client_type.hpp>
#include <models/client_models/region_model.hpp>

namespace ksim
{
    /*
     * For a service in which users are interested in data hosted on behalf of other users that are nearby, but not
     * necessarily with strict boundaries - such as a matchmaking server
     *
     * Divide the location space into small regions, with one chunk per. Each client is interested in the chunk of a
     * random nearby region, but with the choice weighted by resident population of that region.
     *
     * Ideal result:
     * Cities cache the chunks of all nearby regions. Sparse regions cache the nearest city's data.
     */
    class matchmaking_lobby_client_type: public client_type
    {
    public:
        matchmaking_lobby_client_type(const location_model& loc);
        virtual client_work_spec generate(location_model::location_t loc) override;

    private:
        const unsigned int x_cells = 10;
        const unsigned int y_cells = 10;
        const int x_range = 3;
        const int y_range = 3;
        region_model regions;

        std::map<region_model::key_t, chunk_id_t> chunks;
    };
}
