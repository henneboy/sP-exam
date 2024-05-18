//
// Created by Henrik on 18-05-2024.
//

// Test for the ctor and functionality of the vessel example

#include <doctest/doctest.h>
#include <string>
#include "symbol_table.hpp"

TEST_CASE("Symbol table add tests")
{
    symbol_table<std::string, unsigned> table{};
    auto key = "key";
    auto otherKey = "otherKey";
    auto value = 1U;

    bool success1 = table.Add(key, value);
    CHECK(success1);

    bool success2 = table.Add(otherKey, value);
    CHECK(success2);

    bool success3 = table.Add(key, value);
    CHECK(!success3);
}