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
    [[maybe_unused]] key Add(key k, value v){
        table.insert(k, v);
        return k;
    }
};

#endif //SHAPE_EXAMPLE_SYMBOL_TABLE_H
