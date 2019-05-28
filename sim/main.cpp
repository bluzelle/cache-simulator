#include <iostream>
#include <sim/simulation.hpp>
#include <config/sim_config.hpp>

using namespace ksim;

int main(int, char**)
{
    sim_config config;
    simulation sim(config);

    sim.run();
}

