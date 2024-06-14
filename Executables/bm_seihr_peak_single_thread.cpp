//
// Created by Henri on 14/06/2024.
//

#include <benchmark/benchmark.h>
#include "../utilities.h++"

static void bm_seihr_peak_single_thread(benchmark::State& state){
    const auto size = state.range(0);
    SimulateSeihrPeak(COVID19Parameters::NJ_Population);
}

BENCHMARK(bm_seihr_peak_single_thread)->RangeMultiplier(10)->Range(1, 100);
