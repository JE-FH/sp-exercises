/**
   Author: Marius Mikucionis <marius@cs.aau.dk>
   Example from "Combining C++17 Features" by Nicolai Josuttis
   https://youtu.be/6HoxXeEBtW0?t=2241

   Compile:
   g++ -std=c++17 -Wall -DNDEBUG -O3 -o stringsort0_bm stringsort0_bm.cpp -lbenchmark
 */

#include "stringsort.hpp"

#include <benchmark/benchmark.h>
#include <cstring>
#include <cstdlib>

static void stringsort_c(benchmark::State& state)
{
    const auto size = state.range(0);
    for (auto _ : state) {
        state.PauseTiming();
        char** cstrs = gen_cids(size);
        state.ResumeTiming();
        std::qsort(cstrs, size, sizeof(char*), [](const void* a, const void* b) -> int {
            const char* s1 = static_cast<const char*>(a);
            const char* s2 = static_cast<const char*>(b);
            return strcmp(s1 + 2, s2 + 2);
        });
        benchmark::DoNotOptimize(cstrs);
        benchmark::ClobberMemory();
        for (auto i = 0ll; i < size; ++i)
            free(cstrs[i]);
        free(cstrs);
    }
}
BENCHMARK(stringsort_c)->RangeMultiplier(10)->Range(100, 10'000'000);

BENCHMARK_MAIN();
