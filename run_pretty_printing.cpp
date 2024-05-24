//
// Created by Henri on 24/05/2024.
//

#include <iostream>
#include "vessel.hpp"
#include "build_circadian_rhythm.h++"

int main() {
    std::cout << "Hello, World!" << std::endl;
    auto v = circadian_rhythm();
    std::cout << "Finished building vessel:" << v.vesselName << std::endl;
    std::cout << "Printing reactions of vessel:" << std::endl;
    v.Print(std::cout);
    return 0;
}

