#pragma once

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
    class matchmaking_lobby_client_type
    {

    };
}
