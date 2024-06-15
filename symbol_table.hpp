//
// Created by Henrik on 18-05-2024.
//
#include <unordered_map>
#include <stdexcept>

#ifndef SHAPE_EXAMPLE_SYMBOL_TABLE_H
#define SHAPE_EXAMPLE_SYMBOL_TABLE_H

// 3. Implement a generic symbol reactants to store and lookup objects of user-defined key and value types.
// Support failure cases when
//      a) the reactants does not contain a looked up symbol,
//      b) the reactants already contains a symbol that is being added.

template <typename key, typename value>
class symbol_table{
protected:
    std::unordered_map<key, value> table;
public:
    [[maybe_unused]] bool store(key k, value v){
        auto [_, isSuccess] = table.insert( std::make_pair(k, v));
        return isSuccess;
    }

    value lookup(const key& k) const {
        if (!table.contains(k)){
            throw std::invalid_argument("Table lookup failed for: " + k);
        }
        return table.at(k);
    }
};

#endif //SHAPE_EXAMPLE_SYMBOL_TABLE_H
