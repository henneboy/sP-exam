//
// Created by Henri on 22/05/2024.
//
#include <memory>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include <memory>
#include "Vessel.hpp"

#ifndef SHAPE_EXAMPLE_PRINTINGVISITOR_H
#define SHAPE_EXAMPLE_PRINTINGVISITOR_H

template <typename Data, typename Visitor>
concept CanAcceptVisitor = requires(Data&& d, Visitor&& v) { // given an instance c of type T&&
    { d.accept(v) }; // must be able to accept v
};

template <typename Data, typename Visitor>
constexpr auto accepts_v = CanAcceptVisitor<Data, Visitor>;

struct PrintingVisitor
{
    std::ostream& stream;

    template <typename Reaction> requires accepts_v<Reaction, PrintingVisitor>
    void visit(const Reaction& reaction){
        stream << "Starting printing reaction" << std::endl;
    }

    void visit(const double delay){
        stream << delay;
    }
/*
    void visit(const Agent& agent){
        stream << agent.Name;
    }
    */
};

#endif //SHAPE_EXAMPLE_PRINTINGVISITOR_H
