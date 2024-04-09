#include <vector>
#include <future>
#include <random>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <type_traits>

std::vector<int> produce(size_t n){
    auto gen = std::mt19937{std::random_device{}()};
    auto dist = std::uniform_int_distribution<int>{0, 100};
	std::vector<int> rv;
    std::generate_n(std::back_inserter(rv), n, [&] { return dist(gen); });
	return rv;
}

int summarize(std::vector<std::future<std::vector<int>>>&& v){
	return std::accumulate(std::begin(v), std::end(v), 0, [](int a, std::future<std::vector<int>>& b) {
		auto res = b.get();
		return a + std::accumulate(std::cbegin(res), std::cend(res), 0);
	});
}


template <typename T>
struct TD;

template <typename TIn, typename Fn>
	requires std::is_invocable_v<Fn, TIn>
std::future<std::invoke_result_t<Fn, TIn>> and_then(std::future<TIn>&& input, Fn&& fn)
{
    return std::async(fn, input.get());
}




int main(){
	std::vector<std::future<int>> futures;
    for (size_t i = 0; i < 200; i++) {
		futures.emplace_back(and_then(std::async(produce, 200), [](const std::vector<int>& v) -> int {
            return std::accumulate(std::cbegin(v), std::cend(v), 0);
		}));
	}
	auto total = std::accumulate(futures.begin(), futures.end(), 0, [](int a, std::future<int>& f) -> int {
		return a + f.get();
	});

	std::cout << "Total: " << total << std::endl;
}