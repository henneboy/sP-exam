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
    void examplePlot(){
        std::set<std::vector<double>> Y = {{16, 5, 9, 4}, {2, 11, 7, 14}, {3, 10, 6, 15}, {13, 8, 12, 1}};
        plot(Y);
        show();
    }

};

#endif //SP_EXAM_CSVPLOTTER_HPP
