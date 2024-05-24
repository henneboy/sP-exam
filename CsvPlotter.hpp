//
// Created by Henri on 24/05/2024.
//

#ifndef SP_EXAM_CSVPLOTTER_HPP
#define SP_EXAM_CSVPLOTTER_HPP

#include <fstream>
#include <memory>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include <unordered_map>
#include <random>
#include <set>
#include <matplot/matplot.h>

using namespace matplot;

struct CsvPlotter{
    std::ifstream file;
    bool hasReadHeader = false;
    std::vector<std::string> agentsOfInterest;
    std::vector<unsigned> indexesOfAgentsOfInterest;

    explicit CsvPlotter(const std::string& filepath, std::vector<std::string> agents){
        file = std::ifstream {filepath};
        agentsOfInterest = std::move(agents)
    }

    void examplePlot(){
        std::set<std::vector<double>> Y = {{16, 5, 9, 4}, {2, 11, 7, 14}, {3, 10, 6, 15}, {13, 8, 12, 1}};
        plot(Y);
        show();
    }

    std::vector<unsigned> readCsv(){
        if (!hasReadHeader){

        }
    }

    std::vector<std::string> parseLineFromCsv(const char delimiter){
        std::vector<std::string> result;
        std::string line;
        std::getline(file, line);
        size_t pos = 0;
        std::string token;
        while ((pos = line.find(delimiter)) != std::string::npos) {
            token = line.substr(0, pos);
            result.push_back(token);
            line.erase(0, pos + 1);
        }
        return result;
    }

};

#endif //SP_EXAM_CSVPLOTTER_HPP
