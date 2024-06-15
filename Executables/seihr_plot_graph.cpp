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

// Requirement: 5. Demonstrate the application of the library on the three examples (shown in Fig. 3).
// Requirement: 6. Display simulation trajectories of how the amounts change. External tools/libraries can be used to visualize.

int main() {
    auto v = seihr();
    std::cout << "Finished building vessel " << v.vesselName << std::endl;

    Simulator sim{1};

    std::vector<std::string> agentsOfInterest = {"S", "E", "I", "H", "R"};
    //std::vector<std::string> agentsOfInterest = {"H"};
    StateMemorizer memorizer{agentsOfInterest};
    sim.simulate(100.0, v, memorizer);
    std::vector<DataPoint> transformedData{};
    std::ranges::for_each(memorizer.data.begin(), memorizer.data.end(), [](DataPoint& d){
        auto& value = d.state.find("H")->second;
        value *= 1000;
    });
    Plotter::visit(memorizer.data);

    return 0;
}