#include "digits.hpp"
#include <random>
#include <benchmark/benchmark.h>

static auto gen = std::mt19937{std::random_device{}()};

std::vector<int32_t> inputs(const std::size_t N, const int R)
{
    auto res = std::vector<int32_t>(N);
    auto dist = std::uniform_int_distribution<int32_t>{-R, R};
    std::generate_n(std::begin(res), N, [&dist] { return dist(gen); });
    return res;
}

constexpr auto size = 100;
constexpr auto range = 1000000000;

void digits10_div_bm(benchmark::State& state)
{
    const auto data = inputs(state.range(0), state.range(1));
    auto res = data;
    for (auto _ : state) {
        std::transform(std::begin(data), std::end(data), std::begin(res), digits10_div<int32_t>);
        benchmark::DoNotOptimize(res.data());
        benchmark::ClobberMemory();
    }
}
BENCHMARK(digits10_div_bm)->Args({size, range});

void digits10_mul_bm(benchmark::State& state)
{
    const auto data = inputs(state.range(0), state.range(1));
    auto res = data;
    for (auto _ : state) {
        std::transform(std::begin(data), std::end(data), std::begin(res), digits10_mul<int32_t>);
        benchmark::DoNotOptimize(res.data());
        benchmark::ClobberMemory();
    }
}
BENCHMARK(digits10_mul_bm)->Args({size, range});

void digits10_log_bm(benchmark::State& state)
{
    const auto data = inputs(state.range(0), state.range(1));
    auto res = data;
    for (auto _ : state) {
        std::transform(std::begin(data), std::end(data), std::begin(res), digits10_log<int32_t>);
        benchmark::DoNotOptimize(res.data());
        benchmark::ClobberMemory();
    }
}
BENCHMARK(digits10_log_bm)->Args({size, range});

void digits10_div2_bm(benchmark::State& state)
{
    const auto data = inputs(state.range(0), state.range(1));
    auto res = data;
    for (auto _ : state) {
        std::transform(std::begin(data), std::end(data), std::begin(res), digits10_div2<int32_t>);
        benchmark::DoNotOptimize(res.data());
        benchmark::ClobberMemory();
    }
}
BENCHMARK(digits10_div2_bm)->Args({size, range});

void digits10_div3_bm(benchmark::State& state)
{
    const auto data = inputs(state.range(0), state.range(1));
    auto res = data;
    for (auto _ : state) {
        std::transform(std::begin(data), std::end(data), std::begin(res), digits10_div3<int32_t>);
        benchmark::DoNotOptimize(res.data());
        benchmark::ClobberMemory();
    }
}
BENCHMARK(digits10_div3_bm)->Args({size, range});

void digits10_div4_bm(benchmark::State& state)
{
    const auto data = inputs(state.range(0), state.range(1));
    auto res = data;
    for (auto _ : state) {
        std::transform(std::begin(data), std::end(data), std::begin(res), digits10_div4<int32_t>);
        benchmark::DoNotOptimize(res.data());
        benchmark::ClobberMemory();
    }
}
BENCHMARK(digits10_div4_bm)->Args({size, range});

void digits10_div5_bm(benchmark::State& state)
{
    const auto data = inputs(state.range(0), state.range(1));
    auto res = data;
    for (auto _ : state) {
        std::transform(std::begin(data), std::end(data), std::begin(res), digits10_div5<int32_t>);
        benchmark::DoNotOptimize(res.data());
        benchmark::ClobberMemory();
    }
}
BENCHMARK(digits10_div5_bm)->Args({size, range});

void digits10_divn_bm(benchmark::State& state)
{
    const auto data = inputs(state.range(0), state.range(1));
    auto res = data;
    for (auto _ : state) {
        std::transform(std::begin(data), std::end(data), std::begin(res), digits10_divn<int32_t>);
        benchmark::DoNotOptimize(res.data());
        benchmark::ClobberMemory();
    }
}
BENCHMARK(digits10_divn_bm)->Args({size, range});

void digits10_loop_bm(benchmark::State& state)
{
    const auto data = inputs(state.range(0), state.range(1));
    auto res = data;
    for (auto _ : state) {
        std::transform(std::begin(data), std::end(data), std::begin(res), digits10_loop<int32_t>);
        benchmark::DoNotOptimize(res.data());
        benchmark::ClobberMemory();
    }
}
BENCHMARK(digits10_loop_bm)->Args({size, range});

BENCHMARK_MAIN();
