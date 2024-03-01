/// Created by Marius Mikucionis <marius@cs.aau.dk>

#include <benchmark/benchmark.h>
#include <random>

auto make_data(size_t size, int max)
{
    static auto gen = std::default_random_engine{std::random_device{}()};
    static auto dist = std::uniform_int_distribution{0, max};
    auto res = std::vector<int>(size);
    std::generate(res.begin(), res.end(), [] { return dist(gen); });
    return res;
};

static void bm_sort(benchmark::State& state)
{
    const auto size = state.range(0);
    const auto max = state.range(1);
    const auto data = make_data(size, max);
    for (auto _ : state) {
        state.PauseTiming();
        auto input = data;
        state.ResumeTiming();
        sort(input.begin(), input.end());
        benchmark::DoNotOptimize(input.data());  // tells compiler that vv.data() is useful
        benchmark::ClobberMemory();              // flush changes to memory
    }
}
BENCHMARK(bm_sort)->ArgPair(100, 100)->ArgPair(1'000, 100)->ArgPair(10'000, 100)->ArgPair(100'000, 100);
