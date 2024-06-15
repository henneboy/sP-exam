
#include <iostream>
#include "../Vessel.hpp"
#include "../Simulator.hpp"
#include "../Observers/Observer.hpp"
#include "../Examples/build_circadian_rhythm.h++"
#include "../Observers/StateMemorizer.hpp"
#include "../Plotter.hpp"

// Requirement: 5. Demonstrate the application of the library on the three examples (shown in Fig. 2).
// Requirement: 6. Display simulation trajectories of how the amounts change. External tools/libraries can be used to visualize.


int main() {
    auto v = circadian_rhythm();
    std::cout << "Finished building vessel " << v.vesselName << std::endl;

    Simulator sim{1};
    std::vector<std::string> agentsOfInterest = {"A", "C", "R"};
    StateMemorizer memorizer{agentsOfInterest};
    sim.simulate(100.0, v, memorizer);
    Plotter::visit(memorizer.data);
    return 0;
}

