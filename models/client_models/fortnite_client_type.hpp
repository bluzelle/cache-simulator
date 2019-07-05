#pragma once

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
    class fortnite_client_type
    {

    };
}
