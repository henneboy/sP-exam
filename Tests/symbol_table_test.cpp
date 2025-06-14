//
// Created by Henrik on 18-05-2024.
//

#include "doctest/doctest.h"
#include <string>
#include "../symbol_table.hpp"

// Requirement: 9. Implement unit tests (e.g. test symbol table methods, their failure cases)

TEST_CASE("Symbol table add tests (string, unsigned)")
{
    symbol_table<std::string, unsigned> table{};
    auto key = "key";
    auto otherKey = "otherKey";
    auto value = 1U;

    bool success1 = table.store(key, value);
    CHECK(success1);

    bool success2 = table.store(otherKey, value);
    CHECK(success2);

    bool success3 = table.store(key, value);
    CHECK(!success3);
}

TEST_CASE("Symbol table look up tests (string, unsigned)")
{
    symbol_table<std::string, unsigned> table{};
    auto key = "key";
    auto otherKey = "otherKey";
    auto value = 1U;

    table.store(key, value);
    auto result1 = table.lookup(key);
    CHECK((result1 == value));
    CHECK_THROWS_AS(table.lookup(otherKey), std::invalid_argument);
}

TEST_CASE("Symbol table add tests (int, int)")
{
    symbol_table<int, int> table{};
    auto key = 1;
    auto otherKey = 2;
    auto value = 42;

    bool success1 = table.store(key, value);
    CHECK(success1);

    bool success2 = table.store(otherKey, value);
    CHECK(success2);

    bool success3 = table.store(key, value);
    CHECK(!success3);
}

TEST_CASE("Symbol table look up tests (int, int)")
{
    symbol_table<int, int> table{};
    auto key = 1;
    auto otherKey = 2;
    auto value = 42;

    table.store(key, value);
    auto result1 = table.lookup(key);
    CHECK((result1 == value));
    CHECK_THROWS_AS(table.lookup(otherKey), std::invalid_argument);
}