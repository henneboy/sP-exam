//
// Created by Henrik on 15-06-2024.
//

#ifndef SP_EXAM_PRETTY_PRINTING_H
#define SP_EXAM_PRETTY_PRINTING_H
#include <ostream>
#include "Vessel.hpp"

std::ostream& operator<<(std::ostream& o, const Reaction& v) {
    for (const auto& input: v.inputs) {
        o << input;
        if (!(input == v.inputs.back())){
            o << "+";
        }
    }
    o << "--";
    o << v.delay;
    o << "->";
    if (v.outputs.empty()){
        o << Environment::Name;
    }
    for (const auto& output: v.outputs) {
        o << output;
        if (!(output == v.outputs.back())) {
            o << "+";
        }
    }
    o << std::endl;
    return o;
}

std::ostream& operator<<(std::ostream& o, const std::unordered_map<unsigned, Reaction>& v) {
    for (const auto& [index, reaction]: v) {
        o << reaction;
    }
    return o;
}

std::ostream& operator<<(std::ostream& o, const Vessel& v) {
    o << v.vesselName << std::endl;
    o << v.reactions;
    return o;
}


#endif //SP_EXAM_PRETTY_PRINTING_H
