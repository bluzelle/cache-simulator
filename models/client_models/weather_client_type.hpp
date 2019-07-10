#pragma once
#include <models/client_models/region_model.hpp>
#include <models/client_model.hpp>
#include <include/types.hpp>

namespace ksim
{
    /*
     * For a weather service. The location space is divided into small contiguous spaces, each of which corresponds to
     * exactly one chunk
     * - most clients are interested in only the chunk for the area in which they are (local residents)
     * - a minority of clients are interested in the chunk for a random (per the location model) location (travelers)
     *
     * Ideal result: the local weather is cached wherever it is, and additionally, population centers cache the
     * weather of other population centres.
     *
     * TODO: current implementation does not do traveling. There is a bit of complexity wrt how to select locations without
     * improperly influencing the location model but still using its distribution.
     */
    class weather_client_type : public client_type
    {
    public:
        weather_client_type(const location_model& loc);
        virtual client_model::client_work_model generate(location_model::location_t loc) override;

    private:
        const region_model regions;
        std::map<region_model::key_t, chunk_id_t> chunks;
    };
}

