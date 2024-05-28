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
#include "Meta/canAcceptVisitor.hpp"

#ifndef SHAPE_EXAMPLE_PRINTINGVISITOR_H
#define SHAPE_EXAMPLE_PRINTINGVISITOR_H

struct PrintingVisitor
{
    std::ostream& stream;

    template <typename Reaction> requires CanAcceptVisitor<Reaction, PrintingVisitor>
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
