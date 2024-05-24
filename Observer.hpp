//
// Created by Henri on 24/05/2024.
//

#ifndef SHAPE_EXAMPLE_OBSERVER_HPP
#define SHAPE_EXAMPLE_OBSERVER_HPP

#include <random>
#include <unordered_map>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <memory>
#include <fstream>

struct SimulationObserver{
public:
    virtual void accept(const std::unordered_map<std::string, unsigned>& s, double t) = 0;
};

struct StateToFileWriter : public SimulationObserver{
    bool hasWrittenHeader = false;
    std::ofstream file;
    explicit StateToFileWriter(const std::string& filepath){
        file = std::ofstream {filepath};
    }

    void accept(const std::unordered_map<std::string, unsigned>& s, const double t) override{
        if (!hasWrittenHeader){
            file << "time";
            for (auto& pair : s){
                file << ";" << pair.first;
            }
            file << std::endl;
            hasWrittenHeader = true;
        }
        file << t;
        for (auto& pair : s){
            file << ";" << pair.second;
        }
        file << std::endl;
    }
};

#endif //SHAPE_EXAMPLE_OBSERVER_HPP
