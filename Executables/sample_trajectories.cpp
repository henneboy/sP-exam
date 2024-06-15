//
// Created by Henrik on 15-06-2024.
//


#include <iostream>
#include "../Examples/build_sample_trejectory.h++"
#include "../Simulator.hpp"
#include "../Observers/StateMemorizer.hpp"
#include "../Plotter.hpp"

// Requirement: 5. Demonstrate the application of the library on the three examples (shown in Fig. 1).
// Requirement: 6. Display simulation trajectories of how the amounts change. External tools/libraries can be used to visualize.


int main() {
    auto v = sample_trajectory(100, 0, 1);
    std::cout << "Finished building vessel " << v.vesselName << std::endl;

    Simulator sim{1};

    std::vector<std::string> agentsOfInterest = {"A", "B", "C"};
    StateMemorizer memorizer{agentsOfInterest};
    sim.simulate(2000.0, v, memorizer);
    Plotter::visit(memorizer.data);

    return 0;
}