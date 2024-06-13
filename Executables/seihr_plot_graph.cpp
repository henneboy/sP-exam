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
#include "../Plotter.hpp"

int main() {
    auto v = seihr();
    std::cout << "Finished building vessel " << v.vesselName << std::endl;

    std::cout << "Running simulation" << std::endl;
    Simulator sim{1};

    //std::vector<std::string> agentsOfInterest = {"S", "E", "I", "H", "R"};
    std::vector<std::string> agentsOfInterest = {"H"};
    StateMemorizer memorizer{agentsOfInterest};
    sim.simulate(100.0, v, memorizer);
    Plotter::visit(memorizer.data);

    return 0;
}