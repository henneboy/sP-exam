// Test for the ctor and functionality of the vessel example

#include "doctest/doctest.h"
#include "../Vessel.hpp"

TEST_CASE("Vessel ctor test")
{
    auto v = Vessel{"Circadian Rhythm"};
    CHECK(v.reactions.empty());
    CHECK((v.vesselName == "Circadian Rhythm"));
}

TEST_CASE("Vessel successful parse")
{
    const auto gammaA = 1;
    const auto thetaA = 50;
    auto v = Vessel{"Circadian Rhythm"};
    const auto env = Vessel::environment();
    const auto DA = v.add("DA", 1);
    const auto D_A = v.add("D_A", 0);
    const auto A = v.add("A", 0);
    const auto agentMultiOverload = (A + DA);
    const auto agentAndDelayOverload = (D_A) >> thetaA;
    const auto reaction = (A + DA) >> gammaA >>= D_A;
    v.add((A + DA) >> gammaA >>= D_A);
    v.add(A >> gammaA >>= D_A);
    v.add(A >> gammaA >>= env);
}

