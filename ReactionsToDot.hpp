//
// Created by Henri on 28/05/2024.
//

#ifndef SP_EXAM_REACTIONSTODOT_HPP
#define SP_EXAM_REACTIONSTODOT_HPP

#include <unordered_map>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <memory>
#include <fstream>
#include <iomanip>
#include <format>
#include "Vessel.hpp"

// Requirement: 2. Provide pretty-printing of the reaction network in ... b) network graph (e.g. Fig. 4).

struct ReactionsToDot{
    static void makeDotFile(const std::unordered_map<unsigned, Reaction>& reactions, const reactant_store<std::string, unsigned>& store, const std::string& filename){
        std::ofstream of{filename};
        of.flags(std::ofstream::fixed);
        of << "digraph{" << std::endl;
        const auto& reactants = store.getState();
        for (const auto& [agentName, _]: reactants) {
            of << agentName;
            addStatement(agentName, "box", "cyan", of);
        }
        for (const auto& [number, reaction]: reactions) {
            std::string reactionID = std::format("r{}", number);
            of << reactionID;
            addStatement(reaction.delay, "oval", "yellow", of);
            for (const auto& agent: reaction.inputs) {
                of << agent << " -> " << reactionID << std::endl;
            }
            for (const auto& agent: reaction.outputs) {
                of << reactionID << " -> " << agent << std::endl;
            }
        }
        of << "}" << std::endl;
    }
private:

    static std::ofstream& addStatement(const std::string& label, const std::string& shape, const std::string& color, std::ofstream& of){
        of << "[label=" << label << R"(,shape=")" << shape << R"(",style="filled",fillcolor=")" << color << "\"];" << std::endl;
        return of;
    }

    static std::ofstream& addStatement(const double& delay, const std::string& shape, const std::string& color, std::ofstream& of){
        of << "[label=" << delay << R"(,shape=")" << shape << R"(",style="filled",fillcolor=")" << color << "\"];" << std::endl;
        return of;
    }
};
#endif //SP_EXAM_REACTIONSTODOT_HPP
