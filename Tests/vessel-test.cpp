// Test for the ctor and functionality of the vessel example

#include "doctest/doctest.h"
#include "../Vessel.hpp"

TEST_CASE("Vessel ctor test")
{
    auto v = Vessel{"Circadian Rhythm"};
    CHECK(v.reactions.empty());
    CHECK(v.vesselName == "Circadian Rhythm");
}

TEST_CASE("Vessel successful parse")
{
    const auto gammaA = 1;
    const auto thetaA = 50;
    auto v = Vessel{"Circadian Rhythm"};
    const auto env = v.environment();
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

/// number_series class
/*TEST_CASE("Maintain minimum and maximum values")
{
    auto ns = number_series{};
    // TODO: uncomment one test at a time, implement it and check it
    ns.add_value(10);
    CHECK(ns.get_min() == 10);
    CHECK(ns.get_max() == 10);
    SUBCASE("Add greater")
    {
        ns.add_value(15);
        CHECK(ns.get_min() == 10);
        CHECK(ns.get_max() == 15);
        ns.add_value(17);
        CHECK(ns.get_min() == 10);
        CHECK(ns.get_max() == 17);
        ns.add_value(13);
        CHECK(ns.get_min() == 10);
        CHECK(ns.get_max() == 17);
    }
    SUBCASE("Add lesser")
    {
        ns.add_value(5);
        CHECK(ns.get_min() == 5);
        CHECK(ns.get_max() == 10);
        ns.add_value(3);
        CHECK(ns.get_min() == 3);
        CHECK(ns.get_max() == 10);
        ns.add_value(7);
        CHECK(ns.get_min() == 3);
        CHECK(ns.get_max() == 10);
    }
}
*/
