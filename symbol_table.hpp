//
// Created by Henrik on 18-05-2024.
//
#include <unordered_map>

#ifndef SHAPE_EXAMPLE_SYMBOL_TABLE_H
#define SHAPE_EXAMPLE_SYMBOL_TABLE_H

template <typename key, typename value>
class [[maybe_unused]] symbol_table{
    std::unordered_map<key, value> table;
public:
    [[maybe_unused]] bool Add(key k, value v){
        auto [_, isSuccess] = table.emplace( std::make_pair(k, v));
        return isSuccess;
    }
};

#endif //SHAPE_EXAMPLE_SYMBOL_TABLE_H
