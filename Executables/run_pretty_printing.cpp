//
// Created by Henri on 24/05/2024.
//

#include <iostream>
#include "../Vessel.hpp"
#include "../Examples/build_circadian_rhythm.h++"
#include "../Examples/build_seihr.h++"
#include "../pretty_printing.h++"

int main() {
    auto v = circadian_rhythm();
    std::cout << "Finished building vessel:" << v.vesselName << std::endl;
    std::cout << "Printing reactions of vessel:" << std::endl;
    std::cout << v;

    v = seihr();
    std::cout << "Finished building vessel:" << v.vesselName << std::endl;
    std::cout << "Printing reactions of vessel:" << std::endl;
    std::cout << v;

    return 0;
}

