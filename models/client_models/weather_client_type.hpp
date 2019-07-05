#pragma once

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
     */
    class weather_client_type
    {

    };
}

