//
// Created by Henri on 24/05/2024.
//

#ifndef SHAPE_EXAMPLE_OBSERVER_HPP
#define SHAPE_EXAMPLE_OBSERVER_HPP

#include <random>
#include <unordered_map>
#include <utility>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <memory>
#include "DataPoint.hpp"
#include "Plotter.hpp"
#include "Meta/canAcceptVisitor.hpp"

struct SimulationObserver{
public:
    virtual void accept(const std::unordered_map<std::string, unsigned>& s, double t) = 0;
};

struct StateMemorizer : public SimulationObserver{
    std::vector<std::string> agentsOfInterest;
    std::vector<DataPoint> data;

    explicit StateMemorizer(std::vector<std::string> agentsOfInterest) : agentsOfInterest(std::move(agentsOfInterest)){}

    void accept(const std::unordered_map<std::string, unsigned>& s, const double t) override{
        DataPoint d{t};
        for (auto& agentOfInterest: agentsOfInterest) {
            if (!s.contains(agentOfInterest)){
                throw std::logic_error("Could not find: " + agentOfInterest + " in state.");
            }
            auto level = s.at(agentOfInterest);
            d.state.emplace(agentOfInterest, level);
        }
        data.push_back(d);
    }

    template <typename T> requires CanAcceptVisitor<StateMemorizer, T>
    void accept(T plotter){
        plotter.accept(data);
    }
};

#endif //SHAPE_EXAMPLE_OBSERVER_HPP
