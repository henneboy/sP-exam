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
#include "Vessel.hpp"

#ifndef SHAPE_EXAMPLE_SIMULATOR_HPP
#define SHAPE_EXAMPLE_SIMULATOR_HPP

template <typename T>
concept CanAcceptState = requires(T&& d, std::unordered_map<std::string, unsigned>&& v) { // given an instance c of type T&&
{
    d.accept(v) }; // must be able to accept v
};

class Simulator{
    std::random_device rd;
    std::mt19937 gen;

    Simulator() : gen(rd()){}
    explicit Simulator(int seed) : gen(seed){}

public:
    template <CanAcceptState T>
    void simulate(double duration, Vessel& vessel, T observer){
        double t = 0;
        while (t < duration){
            auto [reactionId, delay] = nextReaction(vessel);
            auto currentReaction = vessel.reactions.find(reactionId)->second;
            t += delay;
            performReaction(vessel, currentReaction);
            observer.accept(vessel.table.getState());
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
        double shortestDelay = -1;
        for (const auto& reaction: vessel.reactions) {
            double productOfInputs = 1;
            bool inputExists = false;
            for (const auto& input: reaction.second.inputs){
                auto inputLevel = vessel.table.Lookup(input);
                if (!inputLevel.has_value()){
                    throw std::invalid_argument("Table lookup failed for:" + input);
                }
                productOfInputs *= inputLevel.value();
                inputExists = true;
            }
            if (!inputExists){
                continue;
            }
            std::exponential_distribution<> d(productOfInputs * reaction.second.delay);
            double delay = d(gen);
            if (delay < shortestDelay){
                shortestDelay = delay;
                nextReaction = reaction.first;
            }
        }
        if (shortestDelay == -1){
            throw std::logic_error("No reaction available for simulation.");
        }
        return {nextReaction, shortestDelay};
    }
};

#endif //SHAPE_EXAMPLE_SIMULATOR_HPP
