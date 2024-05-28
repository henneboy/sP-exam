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
#include "Vessel.hpp"

struct ReactionsToDot{
    static void makeDotFile(const std::vector<Reaction>& reactions, reactant_store<std::string, unsigned> store, const std::string& filename){
        std::ofstream of{filename};
        of << "digraph{" << std::endl;
        for (const auto& agent: store.getState()) {
            std::string agentName = agent.first;
            of << agentName;
            addStatement(agentName, "box", "cyan", of);
        }
        unsigned reactionId = 0;
        for (const auto& r: reactions) {
            of << reactionId;
            addStatement(std::to_string(r.delay), "box", "cyan", of);
        }
    }
private:

    static std::ofstream& addStatement(const std::string& label, const std::string& shape, const std::string& color, std::ofstream& of){
        of << "[label=" << label << R"(,shape=")" << shape << R"(",style="filled",fillcolor=")" << color << "\"];)" <<std::endl;
        return of;
    }
};
#endif //SP_EXAM_REACTIONSTODOT_HPP
