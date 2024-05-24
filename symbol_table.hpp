//
// Created by Henrik on 18-05-2024.
//
#include <unordered_map>
#include <optional>

#ifndef SHAPE_EXAMPLE_SYMBOL_TABLE_H
#define SHAPE_EXAMPLE_SYMBOL_TABLE_H

template <typename key, typename value>
class [[maybe_unused]] symbol_table{
protected:
    std::unordered_map<key, value> table;
public:
    [[maybe_unused]] bool Store(key k, value v){
        auto [_, isSuccess] = table.insert( std::make_pair(k, v));
        return isSuccess;
    }

    std::optional<value> Lookup(key k) const {
        auto it = table.find(k);
        if (it != table.end()) {
            return it->second; // Found: return the associated value
        } else {
            return std::nullopt; // Not found: return an empty optional
        }
    }
};

#endif //SHAPE_EXAMPLE_SYMBOL_TABLE_H
