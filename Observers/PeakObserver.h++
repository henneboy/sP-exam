//
// Created by Henri on 13/06/2024.
//

#ifndef SP_EXAM_PEAKOBSERVER_H
#define SP_EXAM_PEAKOBSERVER_H

#include <vector>
#include "Observer.hpp"
#include "../DataPoint.hpp"
#include "../Meta/canAcceptVisitor.hpp"

struct PeakObserver : public SimulationObserver{
    std::string agentOfInterest;
    unsigned peak = 0;

    explicit PeakObserver(std::string agentOfInterest) : agentOfInterest(std::move(agentOfInterest)){}

    void accept(const std::unordered_map<std::string, unsigned>& s, const double t) override{
        if (!s.contains(agentOfInterest)){
            throw std::logic_error("Could not find: " + agentOfInterest + " in state.");
        }
        auto level = s.at(agentOfInterest);
        if (level > peak){
            peak = level;
        }
    }
};


#endif //SP_EXAM_PEAKOBSERVER_H
