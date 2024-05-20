//
// Created by Henrik on 20-05-2024.
//

#include <doctest/doctest.h>
#include <string>
#include "reactant-store.hpp"

// Ensure it still has the functionality of the symbol-table ----------------------------

TEST_CASE("reactant-store add tests (string, unsigned)")
{
    reactant_store<std::string, unsigned> table{};
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

TEST_CASE("reactant-store look up tests (string, unsigned)")
{
    reactant_store<std::string, unsigned> table{};
    auto key = "key";
    auto otherKey = "otherKey";
    auto value = 1U;

    table.Add(key, value);
    auto result1 = table.Lookup(key);
    CHECK(result1.has_value());

    auto result2 = table.Lookup(otherKey);
    CHECK(!result2.has_value());
}

TEST_CASE("reactant-store add tests (int, int)")
{
    reactant_store<int, int> table{};
    auto key = 1;
    auto otherKey = 2;
    auto value = 42;

    bool success1 = table.Add(key, value);
    CHECK(success1);

    bool success2 = table.Add(otherKey, value);
    CHECK(success2);

    bool success3 = table.Add(key, value);
    CHECK(!success3);
}

TEST_CASE("reactant-store look up tests (int, int)")
{
    reactant_store<int, int> table{};
    auto key = 1;
    auto otherKey = 2;
    auto value = 42;

    bool _ = table.Add(key, value);
    auto result1 = table.Lookup(key);
    CHECK(result1.has_value());
    CHECK((value == result1.value()));

    auto result2 = table.Lookup(otherKey);
    CHECK(!result2.has_value());
}

TEST_CASE("reactant-store increment test (int, int)")
{
    reactant_store<int, int> table{};
    auto key = 1;
    auto value = 42;

    table.Add(key, value);
    auto result1 = table.Lookup(key);
    CHECK(result1.has_value());
    CHECK((value == result1.value()));

    table.increment(key);
    auto result2 = table.Lookup(key);
    CHECK((value + 1 == result2.value()));
}

TEST_CASE("reactant-store decrement test (int, int)")
{
    reactant_store<int, int> table{};
    auto key = 1;
    auto value = 42;

    table.Add(key, value);
    auto result1 = table.Lookup(key);
    CHECK(result1.has_value());
    CHECK((value == result1.value()));

    table.decrement(key);
    auto result2 = table.Lookup(key);
    CHECK((value - 1 == result2.value()));
}
