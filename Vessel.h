//
// Created by Henri on 11/04/2024.
//
#include <memory>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include <memory>

#include "Vessel.h"


struct Agent{
    std::string Name;
};

struct AgentTerm{
    std::shared_ptr<Agent> agent;
    std::optional<std::shared_ptr<AgentTerm>> Term;
    explicit AgentTerm(const std::shared_ptr<Agent>& a){
        agent = a.;
    }
    explicit AgentTerm(const Agent& a, const AgentTerm& term) : AgentTerm(a){
        Term = term;
    }
};

struct Reaction{
    std::shared_ptr<AgentTerm> inputAgents;
    std::shared_ptr<AgentTerm> outputAgents;
    double reactionDelay;
    Reaction(std::shared_ptr<AgentTerm> input, double delay, std::shared_ptr<AgentTerm> output){
        inputAgents = std::move(input);
        reactionDelay = delay;
        outputAgents = std::move(output);
    }
};

constexpr std::shared_ptr<AgentTerm> operator+(const Agent& lhs, const AgentTerm& rhs){
    return AgentTerm(lhs, rhs);
}

struct Vessel {
    std::string Name;
    std::vector<Agent> agents;
    std::vector<unsigned> moleculesOfAgents;

    explicit Vessel(std::string name){
        Name = std::move(name);
    }

    std::shared_ptr<Agent> Add(std::string agentName, unsigned initialMolecules){
        auto a = Agent(std::move(agentName));
        agents.push_back(a);
        moleculesOfAgents.push_back(initialMolecules);
        return std::make_shared<Agent>(a);
    }

    void Add()
};
