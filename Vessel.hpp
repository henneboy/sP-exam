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
    explicit Agent(std::string name){
        Name = std::move(name);
    }
    std::string Name;
};

struct Vessel {
    std::string vesselName;
    std::unordered_map<std::string, unsigned> agentLevel;


    explicit Vessel(std::string name){
        vesselName = std::move(name);
        agentLevel = {};
    }

    static Environment environment(){
        return Environment{};
    }

    Agent add(const std::string& agentName, unsigned initialMolecules){
        auto agent = Agent(agentName);
        agentLevel.insert(std::pair(agent.Name, initialMolecules));
        return agent;
    }
};
