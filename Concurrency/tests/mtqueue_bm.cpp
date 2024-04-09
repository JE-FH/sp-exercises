/**
   Author: Marius Mikucionis <marius@cs.aau.dk>
 */

#include "mtqueue.hpp"

#include <benchmark/benchmark.h>

static void mtqueue_bm(benchmark::State& state)
{
    const auto size = state.range(0);
    for (auto _ : state) {
        auto q = mtqueue<int>{};
        for (auto i = 0; i < size; ++i)
            q.put(i);
        auto sum = 0.;
        for (auto val = q.get(); val; val = q.get())
            sum += val;
        benchmark::DoNotOptimize(sum);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(mtqueue_bm)->RangeMultiplier(10)->Range(100, 10'000'000);
