//
// Created by Henri on 12/06/2024.
//

#include <iostream>
#include "../Vessel.hpp"
#include "../ReactionsToDot.hpp"
#include "../Examples/build_circadian_rhythm.h++"
#include "../Examples/build_seihr.h++"

int main() {
    auto circadianVessel = circadian_rhythm();
    std::cout << "Finished building vessel:" << circadianVessel.vesselName << std::endl;
    ReactionsToDot::makeDotFile(circadianVessel.reactions, circadianVessel.reactants, "circadian_dot.txt");

    auto seihrVessel = seihr();
    std::cout << "Finished building vessel:" << seihrVessel.vesselName << std::endl;
    ReactionsToDot::makeDotFile(seihrVessel.reactions, seihrVessel.reactants, "seihr_dot.txt");

    return 0;
}

