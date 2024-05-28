//
// Created by Henri on 24/05/2024.
//

#ifndef SP_EXAM_PLOTTER_HPP
#define SP_EXAM_PLOTTER_HPP

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


struct Plotter{
    static void examplePlot(){
        std::set<std::vector<double>> Y = {
                {16, 5, 9, 4}, {2, 11, 7, 14}, {3, 10, 6, 15}, {13, 8, 12, 1}};
        plot(Y);

        show();
    }

    void accept(){

    }
};

#endif //SP_EXAM_PLOTTER_HPP
