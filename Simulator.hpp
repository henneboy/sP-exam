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

#ifndef SHAPE_EXAMPLE_SIMULATOR_HPP
#define SHAPE_EXAMPLE_SIMULATOR_HPP

template <typename T>
concept CanAcceptState = requires(T&& d, std::unordered_map<std::string, unsigned>& s, const double t) { // given an instance c of type T&&
{
    d.accept(s, t) }; // must be able to accept v and t
};

class Simulator{
    std::random_device rd;
    std::mt19937 gen;

public:
    Simulator() : gen(rd()){}
    explicit Simulator(int seed) : gen(seed){}

    template <CanAcceptState T>
    void simulate(double duration, Vessel& vessel, T& observer){
        std::cout << "Starting simulation" << std::endl;
        double t = 0;
        unsigned iterationCounter = 0;
        unsigned loggingInterval = 1000;
        while (t < duration){
            auto [reactionId, delay] = nextReaction(vessel);
            auto currentReaction = vessel.reactions.find(reactionId)->second;
            t += delay;
            performReaction(vessel, currentReaction);
            observer.accept(vessel.table.getState(), t);
            iterationCounter++;
            if (iterationCounter % loggingInterval == 0){
                std::cout << "Time: " << t << " of total: " << duration << std::endl;
            }
        }
    }

private:
    static void performReaction(Vessel& vessel, const Reaction& r){
        for (auto& input: r.inputs) {
            vessel.table.decrement(input);
        }
        for (auto& output: r.outputs) {
            vessel.table.increment(output);
        }
    }

    std::tuple<unsigned, double> nextReaction(const Vessel& vessel){
        unsigned nextReaction = 0;
        double shortestDelay = std::numeric_limits<double>::max();
        bool foundViableReaction = false;
        for (const auto& reaction: vessel.reactions) {
            double productOfInputs = 1;
            bool missingInput = false;
            for (const auto& input: reaction.second.inputs){
                auto inputLevel = vessel.table.Lookup(input);
                if (!inputLevel.has_value()){
                    throw std::invalid_argument("Table lookup failed for:" + input);
                }
                if (inputLevel.value() == 0){
                    missingInput = true;
                    break;
                }
                productOfInputs *= inputLevel.value();
            }
            if (missingInput){
                continue;
            }
            foundViableReaction = true;
            std::exponential_distribution<> d(productOfInputs * reaction.second.delay);
            double delay = d(gen);
            if (delay < shortestDelay){
                shortestDelay = delay;
                nextReaction = reaction.first;
            }
        }
        if (!foundViableReaction){
            throw std::logic_error("No reaction available for simulation.");
        }
        return {nextReaction, shortestDelay};
    }
};

#endif //SHAPE_EXAMPLE_SIMULATOR_HPP
