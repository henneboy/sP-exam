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
    static void visit(const std::vector<DataPoint>& data){
        std::cout << "Plotting " << data.size() << " data points" << std::endl;
        auto [time, series] = transformData(data);
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
        for (const auto& [agent, _]: data.front().state) {
            std::vector<unsigned> e;
            series.emplace(agent, e);
        }
        for (const auto& d: data) {
            time.push_back(d.time);
            for (const auto& [agent, level]: d.state) {
                series[agent].push_back(level);
            }
        }
        return {time, series};
    };
};

#endif //SP_EXAM_PLOTTER_HPP
