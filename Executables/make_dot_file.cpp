//
// Created by Henri on 12/06/2024.
//

#include <iostream>
#include "../Vessel.hpp"
#include "../build_circadian_rhythm.h++"
#include "../ReactionsToDot.hpp"

int main() {
    auto v = circadian_rhythm();
    std::cout << "Finished building vessel:" << v.vesselName << std::endl;
    std::cout << "Creating dot file of reactions of circadian rhythm" << std::endl;
    ReactionsToDot::makeDotFile(v.reactions, v.table, "circadian_dot");
    return 0;
}

