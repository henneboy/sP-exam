//
// Created by Henrik on 25-05-2024.
//

#include <doctest/doctest.h>
#include <sstream>
#include "PrintingVisitor.h++"

TEST_CASE("PrintingVisitor test")
{
    const auto inputAgent = std::make_shared<Agent>(Agent("input"));
    const auto expr = Expr(std::make_shared<Agent>(Agent("output")));
    const auto partialReaction = PartialReaction(inputAgent, 1.1);
    const auto reaction = Reaction(partialReaction, expr);
    auto os = std::ostringstream{};
    auto visitor = PrintingVisitor(os);
    reaction.accept(visitor);
    CHECK(os.str() == "xd");
}
