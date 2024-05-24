//
// Created by Henrik on 18-05-2024.
//

#include "doctest/doctest.h"
#include <string>
#include "../symbol_table.hpp"

TEST_CASE("Symbol table add tests (string, unsigned)")
{
    symbol_table<std::string, unsigned> table{};
    auto key = "key";
    auto otherKey = "otherKey";
    auto value = 1U;

    bool success1 = table.Store(key, value);
    CHECK(success1);

    bool success2 = table.Store(otherKey, value);
    CHECK(success2);

    bool success3 = table.Store(key, value);
    CHECK(!success3);
}

TEST_CASE("Symbol table look up tests (string, unsigned)")
{
    symbol_table<std::string, unsigned> table{};
    auto key = "key";
    auto otherKey = "otherKey";
    auto value = 1U;

    table.Store(key, value);
    auto result1 = table.Lookup(key);
    CHECK(result1.has_value());

    auto result2 = table.Lookup(otherKey);
    CHECK(!result2.has_value());
}

TEST_CASE("Symbol table add tests (int, int)")
{
    symbol_table<int, int> table{};
    auto key = 1;
    auto otherKey = 2;
    auto value = 42;

    bool success1 = table.Store(key, value);
    CHECK(success1);

    bool success2 = table.Store(otherKey, value);
    CHECK(success2);

    bool success3 = table.Store(key, value);
    CHECK(!success3);
}

TEST_CASE("Symbol table look up tests (int, int)")
{
    symbol_table<int, int> table{};
    auto key = 1;
    auto otherKey = 2;
    auto value = 42;

    table.Store(key, value);
    auto result1 = table.Lookup(key);
    CHECK(result1.has_value());

    auto result2 = table.Lookup(otherKey);
    CHECK(!result2.has_value());
}