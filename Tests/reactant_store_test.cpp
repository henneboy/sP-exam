//
// Created by Henrik on 20-05-2024.
//

#include "../Cmake/doctest/doctest.h"
#include <string>
#include "../reactant_store.hpp"

// Ensure it still has the functionality of the symbol-table ----------------------------

TEST_CASE("reactant-store increment test (int, int)")
{
    reactant_store<int, int> table{};
    auto key = 1;
    auto value = 42;

    table.store(key, value);
    auto result1 = table.lookup(key);
    CHECK(result1);
    CHECK((value == result1));

    table.increment(key);
    auto result2 = table.lookup(key);
    CHECK((value + 1 == result2));
}

TEST_CASE("reactant-store decrement test (int, int)")
{
    reactant_store<int, int> table{};
    auto key = 1;
    auto value = 42;

    table.store(key, value);
    auto result1 = table.lookup(key);
    CHECK(result1);
    CHECK((value == result1));

    table.decrement(key);
    auto result2 = table.lookup(key);
    CHECK((value - 1 == result2));
}
