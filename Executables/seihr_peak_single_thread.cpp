//
// Created by Henri on 12/06/2024.
//

#include <iostream>
#include "../Vessel.hpp"
#include "../Simulator.hpp"
#include "../Observers/Observer.hpp"
#include "../Observers/StateMemorizer.hpp"
#include "../Examples/build_seihr.h++"
#include "../Observers/PeakObserver.h++"

int main() {
    auto v = seihr();
    std::cout << "Finished building vessel " << v.vesselName << std::endl;

    std::cout << "Running simulation" << std::endl;
    Simulator sim{1};
    PeakObserver peakObserver{"H"};
    sim.simulate(100.0, v, peakObserver);
    std::cout << "Peak level: " <<  peakObserver.peak  << ", at time: " << peakObserver.peakTime << std::endl;

    return 0;
}