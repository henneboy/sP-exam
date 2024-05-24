
#include <iostream>
#include "../Vessel.hpp"
#include "../Simulator.hpp"
#include "../Observer.hpp"
#include "../build_circadian_rhythm.h++"

int main() {
    auto v = circadian_rhythm();
    std::cout << "Finished building vessel " << v.vesselName << std::endl;

    std::cout << "Running simulation" << std::endl;
    Simulator sim{1};
    StateToFileWriter toFileWriter{"output.csv"};
    sim.simulate(100.0, v, toFileWriter);

    return 0;
}

