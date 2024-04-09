/**
 * Purpose: try out various API designs using lambda expressions.
 * @author Marius Mikucionis <marius@cs.aau.dk>
 */
#include <sstream>
#include <iostream>
#include <vector>
#include <functional>
#include <memory>
#include <random>
#include <algorithm>
#include <numeric>
#include <benchmark/benchmark.h>

/**
Storage class encapsulates some data, where the storage mechanism is hidden from the user.
Instead of giving direct access, the class provides a number of methods to access the data.
*/
template <typename T>
class storage
{
    std::vector<std::unique_ptr<T>> data;

public:
    storage(size_t size) {
        if constexpr (std::is_arithmetic_v<T>) {
            // sample code just to fill the storage with numbers.
            auto rng = std::mt19937(std::random_device{}());
            using Dist = std::conditional_t<std::is_integral_v<T>,
                                            std::uniform_int_distribution<T>,
                                            std::uniform_real_distribution<T>>;
            auto dist = Dist{-100, 100};
            data.resize(size);
            std::generate(std::begin(data), std::end(data),
                          [&dist,&rng]{ return std::make_unique<T>(dist(rng)); });
        }
    }

    const std::vector<T> get_values() const {
        auto copy = std::vector<T>{};
        copy.reserve(data.size());
        for (auto&& e: data)
            copy.push_back(*e);
        return copy;
    }

    template <typename Fn>
    void apply(Fn&& fn) const {
        static_assert(std::is_invocable_v<Fn,T>, "expecting function over (T)");
        std::for_each(std::begin(data), std::end(data),
                      [fn=std::forward<Fn>(fn)](auto&& ptr)
					  { fn(*ptr); });
    }

    void for_each(std::function<void(T)> fn) const {
        std::for_each(std::begin(data), std::end(data),
                      [&fn](auto&& ptr){ fn(*ptr); });
    }

    template <typename Fn>
    auto accumulate(T init, Fn&& fn) const {
        static_assert(std::is_invocable_v<Fn,T,T>, "expecting function over (T,T)");
        return std::accumulate(std::begin(data), std::end(data), init,
                               [fn=std::forward<Fn>(fn)](const T& v, const std::unique_ptr<T>& p)
							   { return fn(v, *p); });
    }

    auto combine(T init, std::function<T(T,T)> fn) const {
        return std::accumulate(std::begin(data), std::end(data), init,
                               [&fn](const T& v, const std::unique_ptr<T>& p)
							   { return fn(v, *p); });
    }
};

std::string try_printer()
{
    auto os = std::ostringstream{};
    auto d = storage<int>{100};
    auto printer = [&os](auto&& e){ os << e << " "; };
    // Method 1: ranged-loop
    for (auto&& e: d.get_values())
        printer(e);
    os << std::endl;
    // Method 2: pass function by reference
    d.apply(printer);
    os << std::endl;
    // Method 3: pass function by std::function
    d.for_each(printer);
    os << std::endl;
    return os.str();
    /** TODO:
        1) Figure out what each function call is doing:
           get_values, apply, for_each.
        2) Discuss pros and cons of each function interface. Which one do you prefer?
        3) Create a benchmark to compare their performance.
     */
}

static void bm_get_values(benchmark::State& state) {
    const auto size = state.range(0);
    auto d = storage<double>{(size_t) size};
    for (auto _ : state) {
        state.PauseTiming();
        auto sum1 = 0.0;
        state.ResumeTiming();
        for (auto&& e : d.get_values())
            sum1 += e;
        benchmark::DoNotOptimize(sum1);
        benchmark::ClobberMemory();
    }
}

static void bm_for_each(benchmark::State& state)
{
    const auto size = state.range(0);
    auto d = storage<double>{(size_t)size};
    for (auto _ : state) {
        state.PauseTiming();
        auto sum1 = 0.0;
        state.ResumeTiming();
        d.for_each([&sum = sum1](auto&& e) { sum += e; });
        benchmark::DoNotOptimize(sum1);
        benchmark::ClobberMemory();
    }
}


static void bm_accumulate(benchmark::State& state)
{
    auto adder = [](auto&& e1, auto&& e2) { return e1 + e2; };
    const auto size = state.range(0);
    auto d = storage<double>{(size_t)size};
    for (auto _ : state) {
        state.PauseTiming();
        auto sum1 = 0.0;
        state.ResumeTiming();
        sum1 = d.accumulate(0, adder);
        benchmark::DoNotOptimize(sum1);
        benchmark::ClobberMemory();
    }
}

static void bm_combine(benchmark::State& state)
{
    auto adder = [](auto&& e1, auto&& e2) { return e1 + e2; };
    const auto size = state.range(0);
    auto d = storage<double>{(size_t)size};
    for (auto _ : state) {
        state.PauseTiming();
        auto sum1 = 0.0;
        state.ResumeTiming();
        sum1 = d.combine(0, adder);
        benchmark::DoNotOptimize(sum1);
        benchmark::ClobberMemory();
    }
}


std::string try_adder()
{
    auto os = std::ostringstream{};
    auto d = storage<double>{100};
    auto adder = [](auto&& e1, auto&& e2) { return e1+e2; };
    auto sum1 = 0.0;
    // Method 1: ranged-loop
    for (auto&& e: d.get_values())
        sum1 += e;
    os << sum1 << std::endl;
    // Method 2: pass function by std::function
    auto sum2 = 0.0;
    d.for_each([&sum=sum2](auto&& e){ sum += e; });
    os << sum2 << std::endl;
    // Method 3: pass function by reference
    os << d.accumulate(0, adder) << std::endl;
    // Method 4: pass function by std::function
    os << d.combine(0, adder) << std::endl;
    return os.str();
    /** TODO:
        1) Figure out what each function call is doing:
           get_values, for_each, accumulate, combine.
        2) Discuss pros and cons of each function interface. Which one do you prefer?
        3) Create a benchmark to compare their performance.
     */
}

BENCHMARK(bm_get_values)->Args({100})->Args({10000});
BENCHMARK(bm_accumulate)->Args({100})->Args({10000});
BENCHMARK(bm_for_each)->Args({100})->Args({10000});
BENCHMARK(bm_combine)->Args({100})->Args({10000});


/** Tips and tricks for benchmarking:
1) either use Google Benchmark, or your own benchmark utility:
   see solution to exercise 5.1, or
   examples code at at the bottom of https://en.cppreference.com/w/cpp/language/attributes/likely
2) use different storage sizes and inspect if the performance changes.
*/
