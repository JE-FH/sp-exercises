#pragma once
#include <thread>
#include <vector>
#include <mutex>
#include <shared_mutex>
#include <functional>
#include <queue>
#include <iterator>
#include <future>
#include <type_traits>

class TPool {
	std::vector<std::jthread> _threads;
    std::queue<std::function<void()>> _tasks;
	std::condition_variable _cv;
	std::mutex _mutex;
	bool _stop;
public:
	TPool(size_t threadCount) {
		std::generate_n(std::back_inserter(_threads), threadCount, [&] { 
			return std::jthread([&] { 
				threadIdle(); 
			});
		});
	}

	TPool(const TPool&) = delete;

	~TPool() {
		_stop = true;
		_cv.notify_all();
		
		for (auto& t : _threads) {
			t.join();
		}
	}

	void threadIdle() {
		while (!_stop) {
			std::unique_lock lock{_mutex};
			while (_tasks.empty() && !_stop)
				_cv.wait(lock);
			if (_stop) {
				return;
			}
			auto f = std::move(_tasks.front());
			_tasks.pop();
			f();
		}
	}

	template<typename F, typename... TArgs>
		requires std::is_invocable_v<F, TArgs...>
	std::future<std::invoke_result_t<F, TArgs...>> schedule(F&& f, TArgs&&... args)
	{
		using Frv = std::invoke_result_t<F, TArgs...>;
		std::promise<Frv> p;//, f = std::forward<F>(f), ... args = std::forward<TArgs>(args)
		auto future = p.get_future();
		{
			std::scoped_lock lock{_mutex};
			_tasks.emplace([p = std::move(p), f = std::forward<F>(f), ... args = std::forward<TArgs>(args)]() mutable {
				if constexpr (std::is_same_v<Frv, void>) {
					std::invoke(std::forward<F>(f), std::forward<TArgs>(args)...);
					p.set_value();
				} else {
					std::invoke(std::forward<F>(f), std::forward<TArgs>(args)...);
					p.set_value(f(std::forward<TArgs>(args)...));
				}
			});
		}
		_cv.notify_one();
		return future;
	}
};