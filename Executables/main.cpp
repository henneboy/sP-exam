
#include <iostream>
#include "../Vessel.hpp"
#include "../Simulator.hpp"
#include "../Observers/Observer.hpp"
#include "../Examples/build_circadian_rhythm.h++"
#include "../Observers/StateMemorizer.hpp"
#include "../Plotter.hpp"

int main() {
    auto v = circadian_rhythm();
    std::cout << "Finished building vessel " << v.vesselName << std::endl;

    std::cout << "Running simulation" << std::endl;

    Simulator sim{1};
    std::vector<std::string> agentsOfInterest = {"A", "C", "R"};
    StateMemorizer memorizer{agentsOfInterest};
    sim.simulate(100.0, v, memorizer);
    //Plotter::examplePlot();
    Plotter::visit(memorizer.data);
    return 0;
}

