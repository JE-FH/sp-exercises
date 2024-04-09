/**
   Author: Marius Mikucionis <marius@cs.aau.dk>
   Example from "Combining C++17 Features" by Nicolai Josuttis
   https://youtu.be/6HoxXeEBtW0?t=2241

   Requires:
   parallel implementation using openmp support (g++-9)

   Compile:
   g++ -std=c++17 -Wall -DNDEBUG -O3 -fopenmp -o stringsort3 stringsort3_bm.cpp

 */

#include "stringsort.hpp"

#include <benchmark/benchmark.h>
#include <parallel/algorithm>  // GNU parallel implementation based on OpenMP
#include <string_view>
#include <algorithm>

static void stringsort_compare_openmp(benchmark::State& state)
{
    for (auto _ : state) {
        state.PauseTiming();
        auto coll = gen_ids(state.range(0));
        state.ResumeTiming();
        // https://stackoverflow.com/a/51031461/2685239
        __gnu_parallel::sort(std::begin(coll), std::end(coll), [](const auto& a, const auto& b) -> bool {
            return a.compare(2, a.length() - 2, b, 2) < 0;
        });
        benchmark::DoNotOptimize(coll.data());
        benchmark::ClobberMemory();
    }
}
BENCHMARK(stringsort_compare_openmp)->RangeMultiplier(10)->Range(100, 10'000'000);

static void stringsort_sv_openmp(benchmark::State& state)
{
    for (auto _ : state) {
        state.PauseTiming();
        auto coll = gen_ids(state.range(0));
        state.ResumeTiming();
        // https://stackoverflow.com/a/51031461/2685239
        __gnu_parallel::sort(std::begin(coll), std::end(coll), [](const auto& a, const auto& b) -> bool {
            return std::string_view{a}.substr(2) < std::string_view{b}.substr(2);
        });
        benchmark::DoNotOptimize(coll.data());
        benchmark::ClobberMemory();
    }
}
BENCHMARK(stringsort_sv_openmp)->RangeMultiplier(10)->Range(100, 10'000'000);

BENCHMARK_MAIN();
