//
// Created by Henri on 24/05/2024.
//

#ifndef SP_EXAM_PLOTTER_HPP
#define SP_EXAM_PLOTTER_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <matplot/matplot.h>

using namespace matplot;


struct Plotter{
    static void examplePlot(){
        std::vector<double> X = {2,4,6,8};
        std::set<std::vector<double>> Y = {
                {16, 5, 9, 4}, {2, 11, 7, 14}, {3, 10, 6, 15}, {13, 8, 12, 1}};
        plot(X, Y);

        show();
    }

    static void visit(const std::vector<DataPoint>& data){
        std::cout << "Plotting " << data.size() << " data points" << std::endl;
        auto [time, series] = transformData(data);
        std::cout << "Transforming yielded " << time.size() << " data points" << std::endl;
        hold(on);
        for (const auto& s: series) {
            auto p = plot(time, s.second);
            p->display_name(s.first);
        }
        hold(off);
        ::matplot::legend({});
        show();
    }

    static std::tuple<std::vector<double>, std::unordered_map<std::string, std::vector<unsigned>>> transformData(const std::vector<DataPoint>& data){
        std::vector<double> time;
        std::unordered_map<std::string, std::vector<unsigned>> series;
        for (const auto& s: data.front().state) {
            std::vector<unsigned> e;
            series.emplace(s.first, e);
        }
        std::unordered_map<std::string, unsigned> prevState{};
        for (const auto& d: data) {
            if (d.state == prevState){
                continue;
            }
            time.push_back(d.time);
            for (const auto& pair: d.state) {
                series[pair.first].push_back(pair.second);
            }
            prevState = d.state;
        }
        return {time, series};
    };
};

#endif //SP_EXAM_PLOTTER_HPP
