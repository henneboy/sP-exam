//
// Created by Henri on 12/06/2024.
//

#ifndef SP_EXAM_STATEMEMORIZER_HPP
#define SP_EXAM_STATEMEMORIZER_HPP

#include <vector>
#include "Observer.hpp"
#include "DataPoint.hpp"
#include "Meta/canAcceptVisitor.hpp"

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

    template <typename T> requires CanAcceptVisitor<T, std::vector<DataPoint>>
    void accept(T visitor){
        visitor.visit(data);
    }
};

#endif //SP_EXAM_STATEMEMORIZER_HPP
