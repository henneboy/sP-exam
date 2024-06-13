//
// Created by Henri on 23/05/2024.
//
#include <memory>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include <memory>
#include <unordered_map>
#include <random>
#include "Meta/CanAcceptState.hpp"
#include "Vessel.hpp"

#ifndef SHAPE_EXAMPLE_SIMULATOR_HPP
#define SHAPE_EXAMPLE_SIMULATOR_HPP

class Simulator{
    std::random_device rd;
    std::mt19937 gen;

public:
    Simulator() : gen(rd()){}
    explicit Simulator(int seed) : gen(seed){}

    template <CanAcceptState T>
    void simulate(double duration, Vessel& vessel, T& observer, bool logStatusToConsole){
        if (logStatusToConsole)
            std::cout << "Starting simulation" << std::endl;
        double t = 0;
        unsigned iterationCounter = 0;
        unsigned loggingInterval = 5000;
        while (t < duration){
            observer.accept(vessel.table.getState(), t);
            auto [reactionId, delay] = nextReaction(vessel);
            auto currentReaction = vessel.reactions.find(reactionId)->second;
            t += delay;
            performReaction(vessel, currentReaction);
            iterationCounter++;
            if (logStatusToConsole && iterationCounter % loggingInterval == 0){

                std::cout << "Time: " << t << " of total: " << duration << std::endl;
            }
        }
        observer.accept(vessel.table.getState(), t);
    }

private:
    static void performReaction(Vessel& vessel, const Reaction& r) {
        for (auto& input: r.inputs) {
            vessel.table.decrement(input);
        }
        for (auto& output: r.outputs) {
            vessel.table.increment(output);
        }
    }

    std::tuple<unsigned, double> nextReaction(const Vessel& vessel) {
        unsigned nextReaction = 0;
        double shortestDelay = std::numeric_limits<double>::max();
        bool foundViableReaction = false;
        for (const auto& reaction: vessel.reactions) {
            auto delay = calculateDelay(reaction.second, vessel);
            if (delay.has_value()){
                foundViableReaction = true;
                if (delay.value() < shortestDelay){
                    shortestDelay = delay.value();
                    nextReaction = reaction.first;
                }
            }
        }
        if (!foundViableReaction){
            throw std::logic_error("No reaction available for simulation.");
        }
        return {nextReaction, shortestDelay};
    }

    std::optional<double> calculateDelay(const Reaction& reaction, const Vessel& vessel){
        double productOfInputs = 1;
        for (const auto& input: reaction.inputs){
            auto inputLevel = vessel.table.lookup(input);
            if (inputLevel == 0){
                return std::nullopt;
            }
            productOfInputs *= inputLevel;
        }
        std::exponential_distribution<> d(productOfInputs * reaction.delay);
        return d(gen);
    }
};

#endif //SHAPE_EXAMPLE_SIMULATOR_HPP
