/**
   Author: Marius Mikucionis <marius@cs.aau.dk>
   Example from "Combining C++17 Features" by Nicolai Josuttis
   https://youtu.be/6HoxXeEBtW0?t=2241

   Requires:
   g++-9 libtdd-dev (e.g. Ubuntu 19.10)

   Compile:
   g++ -std=c++17 -Wall -DNDEBUG -O3 -o stringsort4_bm stringsort4_bm.cpp -ltbb

 */

#include "stringsort.hpp"

#include <benchmark/benchmark.h>
#include <string_view>
#include <execution>  // stdc++ based on Intel Thread Building Blocks
#include <algorithm>

static void stringsort_compare_tbb(benchmark::State& state)
{
    for (auto _ : state) {
        state.PauseTiming();
        auto coll = gen_ids(state.range(0));
        state.ResumeTiming();
        // https://stackoverflow.com/a/55989883/2685239
        std::sort(std::execution::par, std::begin(coll), std::end(coll),
                  [](const auto& a, const auto& b) -> bool { return a.compare(2, a.length() - 2, b, 2) < 0; });
        benchmark::DoNotOptimize(coll.data());
        benchmark::ClobberMemory();
    }
}
BENCHMARK(stringsort_compare_tbb)->Arg(100u)->RangeMultiplier(10)->Range(100, 10'000'000);

static void stringsort_sv_tbb(benchmark::State& state)
{
    for (auto _ : state) {
        state.PauseTiming();
        auto coll = gen_ids(state.range(0));
        state.ResumeTiming();
        // https://stackoverflow.com/a/55989883/2685239
        std::sort(std::execution::par, std::begin(coll), std::end(coll), [](const auto& a, const auto& b) -> bool {
            return std::string_view{a}.substr(2) < std::string_view{b}.substr(2);
        });
        benchmark::DoNotOptimize(coll.data());
        benchmark::ClobberMemory();
    }
}
BENCHMARK(stringsort_sv_tbb)->Arg(100u)->RangeMultiplier(10)->Range(100, 10'000'000);

BENCHMARK_MAIN();
