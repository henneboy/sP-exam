//
// Created by Henrik on 20-05-2024.
//
#include <unordered_map>
#include <stdexcept>
#include "symbol_table.hpp"

#ifndef SHAPE_EXAMPLE_REACTANT_STORE_H
#define SHAPE_EXAMPLE_REACTANT_STORE_H

template <typename key, typename value> requires std::incrementable<value>
class reactant_store : public symbol_table<key, value> {
    void crement(key k, bool increment){
        auto it = this->table.find(k);
        if (it != this->table.end()) {
            if (increment){
                ++(it->second);
            } else {
                --(it->second);
            }
        } else {
            throw std::invalid_argument("The following key does not exist: " + k);
        }
    }

public:
    void increment(key k){
        crement(k, true);
    }

    void decrement(key k){
        crement(k, false);
    }

    std::unordered_map<key, value> getState(){
        return this->table;
    }
};

#endif //SHAPE_EXAMPLE_REACTANT_STORE_H
