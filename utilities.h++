//
// Created by Henri on 14/06/2024.
//


#ifndef SP_EXAM_UTILITIES_H
#define SP_EXAM_UTILITIES_H


#include "Observers/PeakObserver.h++"
#include "Examples/build_seihr.h++"
#include "thread_pool.h++"
#include <type_traits>
#include <vector>

unsigned static SimulateSeihrPeak(size_t N){
    auto v = seihr(N);
    Simulator sim{};
    PeakObserver peakObserver{"H"};
    sim.simulate(100.0, v, peakObserver);
    return peakObserver.peak;
}

struct COVID19Parameters{
    const static size_t NJ_Population = 589755;
    const static size_t DK_Population = 5822763;
};

// Calculate the average as size_t.
template<typename T> requires std::is_arithmetic_v<T>
size_t average(std::vector<T> results){
    auto sum = accumulate(results.begin(), results.end(), 0);

    // average of the vector elements
    return sum / results.size();
}

#endif //SP_EXAM_UTILITIES_H
