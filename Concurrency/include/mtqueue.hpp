#ifndef CONCURRENCY_MTQUEUE_H
#define CONCURRENCY_MTQUEUE_H

#include <optional>
#include <list>
#include <queue>
#include <mutex>
template <typename T>
class mtqueue
{
    std::queue<T, std::deque<T>> container;
    std::mutex _m;
    std::condition_variable _cv;
public:
    void put(T&& item) { 
        std::scoped_lock lock{_m};
        container.push(std::move(item));
        _cv.notify_one();
    }
    void put(const T& item) {
        std::scoped_lock lock{_m};
        container.push(item);
        _cv.notify_one();
    }
    T get()
    {
        std::unique_lock lock {_m};
        while (container.empty())
            _cv.wait(lock);
        auto res = std::move(container.front());
        container.pop();
        return res;
    }
};

#endif  // CONCURRENCY_MTQUEUE_H
