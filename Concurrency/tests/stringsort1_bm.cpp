/**
   Author: Marius Mikucionis <marius@cs.aau.dk>
   Example from "Combining C++17 Features" by Nicolai Josuttis
   https://youtu.be/6HoxXeEBtW0?t=2241

   Compile:
   g++ -std=c++17 -Wall -DNDEBUG -O3 -o stringsort1_bm stringsort1_bm.cpp -lbenchmark
 */

#include "stringsort.hpp"

#include <benchmark/benchmark.h>
#include <algorithm>

static void stringsort_naive(benchmark::State& state)
{
    for (auto _ : state) {
        state.PauseTiming();
        auto coll = gen_ids(state.range(0));
        state.ResumeTiming();
        std::sort(std::begin(coll), std::end(coll),
                  [](const auto& a, const auto& b) { return a.substr(2) < b.substr(2); });
        benchmark::DoNotOptimize(coll.data());
        benchmark::ClobberMemory();
    }
}

BENCHMARK(stringsort_naive)->RangeMultiplier(10)->Range(100, 10'000'000);

BENCHMARK_MAIN();
