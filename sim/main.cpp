#include <iostream>
#include <sim/simulation.hpp>
#include <config/sim_config.hpp>
#include <options/options.hpp>

using namespace ksim;

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cerr << "no options files specified\n";
        return -1;
    }

    options options;

    for(int i=1; i<argc; i++)
    {
        options.merge(argv[i]);
    }

    sim_config config(options);
    simulation sim(config, options);

    sim.run();
}

