//
// Created by Henri on 11/04/2024.
//
#include <memory>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include <memory>
#include <unordered_map>

struct Var{};

struct Environment : Var{};

struct Agent : Var{
    std::string Name;
    explicit Agent(std::string name){
        Name = std::move(name);
    }
};



struct Vessel {
    std::string vesselName;
    std::vector<Agent> agents{};
    std::vector<unsigned> moleculeAmount{};


    explicit Vessel(std::string name){
        vesselName = std::move(name);
    }

    static Environment environment(){
        return Environment{};
    }

    Agent add(const std::string& agentName, unsigned initialAmount){
        auto agent = Agent(agentName);
        agents.push_back(agent);
        moleculeAmount.push_back(initialAmount);
        return agent;
    }
};
