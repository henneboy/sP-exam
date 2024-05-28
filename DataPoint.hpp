//
// Created by Henri on 28/05/2024.
//

#ifndef SP_EXAM_DATAPOINT_HPP
#define SP_EXAM_DATAPOINT_HPP

#include <string>
#include <unordered_map>

struct DataPoint{
    explicit DataPoint(double t) : time{t}{}
    double time;
    std::unordered_map<std::string, unsigned> state;
};

#endif //SP_EXAM_DATAPOINT_HPP
