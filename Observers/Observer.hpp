//
// Created by Henri on 24/05/2024.
//

#ifndef SHAPE_EXAMPLE_OBSERVER_HPP
#define SHAPE_EXAMPLE_OBSERVER_HPP

#include <unordered_map>
#include <string>
#include <memory>

struct SimulationObserver{
public:
    virtual void accept(const std::unordered_map<std::string, unsigned>& s, double t) = 0;
    virtual ~SimulationObserver() = default;
};

#endif //SHAPE_EXAMPLE_OBSERVER_HPP
