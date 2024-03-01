/// Created by Marius Mikucionis <marius@cs.aau.dk>
#include "number_series.hpp"
#include <benchmark/benchmark.h>

auto make_vv(size_t ns_number, size_t ns_length)
{
    using data_series::number_series;
    auto vv = std::vector<number_series>{};
    vv.reserve(ns_number);  // preallocate memory

    for (size_t i = 0; i < ns_number; i++) {
        vv.push_back(number_series::make_random(ns_length));
    }

    return vv;
};

auto make_wrapper(size_t ns_number, size_t ns_length)
{
    using data_series::number_series_wrap;
    auto vw = std::vector<number_series_wrap>{};
    vw.reserve(ns_number);  // preallocate memory

    for (size_t i = 0; i < ns_number; i++) {
        vw.push_back(number_series_wrap::make_random(ns_length));
    }

    return vw;
};

static void bm_ns_sort(benchmark::State& state)
{
    const auto ns_number = state.range(0);
    const auto ns_length = state.range(1);
    const auto input = make_vv(ns_number, ns_length);
    for (auto _ : state) {
        state.PauseTiming();
        auto vv = input;
        state.ResumeTiming();
        std::sort(vv.begin(), vv.end());
        benchmark::DoNotOptimize(vv.data());  // tells compiler that vv.data() is useful
        benchmark::ClobberMemory();           // flush changes to memory
    }
}
BENCHMARK(bm_ns_sort)->ArgPair(100'000, 100);

static void bm_ns_wrap_sort(benchmark::State& state)
{
    const auto ns_number = state.range(0);
    const auto ns_length = state.range(1);
    const auto input = make_wrapper(ns_number, ns_length);
    for (auto _ : state) {
        state.PauseTiming();
        auto vw = input;
        state.ResumeTiming();
        std::sort(vw.begin(), vw.end());
        benchmark::DoNotOptimize(vw.data());  // tells compiler that vw.data() is useful
        benchmark::ClobberMemory();           // flush changes to memory
    }
}
BENCHMARK(bm_ns_wrap_sort)->ArgPair(100'000, 100);
