#pragma once
#include <models/location_model.hpp>
#include <models/client_type.hpp>
#include <include/types.hpp>
#include <models/client_models/region_model.hpp>

namespace ksim
{
    /*
     * For a game in which the users are distributed across an ingame location space and primarily interested in
     * data for their and nearby locations in that space. This is most open world/sandboxy mmos.
     *
     * Build a separate location model. Divide that space into small regions, with one chunk per. Each client is
     * interested in the chunk that corresponds to a random <per location model> location in that space.
     *
     * Ideal result:
     * population centres in the virtual space are cached at population centres in the real space. Sparse real
     * regions do not cache much, and sparse virtual regions are not cached anywhere.
     */
    class eve_client_type : public client_type
    {
    public:
        eve_client_type();

        virtual client_work_spec generate(location_model::location_t loc) override;

    private:
        location_model virtual_location_model;
        const region_model regions;

        std::map<region_model::key_t, chunk_id_t> chunks;
    };
}

