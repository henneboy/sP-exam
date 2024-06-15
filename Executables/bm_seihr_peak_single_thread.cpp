//
// Created by Henri on 14/06/2024.
//

#include <benchmark/benchmark.h>
#include "../utilities.h++"

// 10. Benchmark and compare the stochastic simulation performance (e.g. the time it takes to compute 100 simulations
//a single core, multiple cores, or improved implementation). Record the timings and make your conclusions.
unsigned SimulateSeihrPeak_ThreadPool(size_t N, size_t iterations)
{
    vector<unsigned> results{};

    // Create a thread pool with 4 threads
    ThreadPool pool(SimulateSeihrPeak, N, results, iterations);

    pool.waitForCompletion();

    // average of the vector elements
    return average(results);
}


static void bm_seihr_peak_single_thread(benchmark::State& state){
    const auto iterations = state.range(0);
    for (auto _ : state) {
        for (int i = 0; i < iterations; ++i) {
            auto result = SimulateSeihrPeak(COVID19Parameters::NJ_Population);
            benchmark::DoNotOptimize(result);
            benchmark::ClobberMemory();
        }
    }
}

static void bm_seihr_peak_multi_thread(benchmark::State& state){
    const auto iterations = state.range(0);
    for (auto _ : state) {
        auto result = SimulateSeihrPeak_ThreadPool(COVID19Parameters::NJ_Population, iterations);
        benchmark::DoNotOptimize(result);
        benchmark::ClobberMemory();
    }
}

BENCHMARK(bm_seihr_peak_single_thread)->Unit(benchmark::kSecond)->RangeMultiplier(10)->Range(1, 100)->Iterations(1);
//BENCHMARK(bm_seihr_peak_single_thread)->Unit(benchmark::kSecond)->Arg(COVID19Parameters::DK_Population)->Iterations(10);


BENCHMARK(bm_seihr_peak_multi_thread)->Unit(benchmark::kSecond)->RangeMultiplier(10)->Range(1, 100)->Iterations(1);
