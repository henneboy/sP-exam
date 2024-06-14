//
// Created by Henri on 12/06/2024.
//

#include <iostream>
#include "../Vessel.hpp"
#include "../Simulator.hpp"
#include "../utilities.h++"

int main() {
    auto peak = SimulateSeihrPeak(COVID19Parameters::NJ_Population);
    std::cout << "Peak level: " <<  peak  << std::endl;

    return 0;
}