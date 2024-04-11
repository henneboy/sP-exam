/// Created by Marius Mikucionis <marius@cs.aau.dk>

/** Unit tests for number_series */

//#include "number_series.hpp"

#include <doctest/doctest.h>

//using namespace data_series;

TEST_CASE("Dummy test case")
{
    CHECK(1==2);
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
