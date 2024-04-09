#include "mtqueue.hpp"
#include <random>
#include <iostream>
#include <thread>
#include "tpool.hpp"

void produce(mtqueue<int>& q, size_t count)
{
    auto gen = std::mt19937{std::random_device{}()};
    auto dist = std::uniform_int_distribution<int>{0, 100};
    for (size_t i = 0; i < count; i++) {
        q.put(dist(gen));
    }
    // TODO: create producer routine: put `count` random numbers into the queue
}

void consume(mtqueue<int>& q, size_t count)
{
    for (size_t i = 0; i < count; i++) {
        std::cout << q.get();
    }
    // TODO: create consumer routine: fetch and print `count` values from the queue
}

int main()
{
    mtqueue<int> q;
    TPool pool(100);

    for (int i = 0; i < 100; i++) {
        pool.schedule(produce, std::ref(q), 100);
        pool.schedule(consume, std::ref(q), 100);
    }
    // TODO: create an instance of a queue
    // TODO: spawn multiple threads for producer and consumer to use the queue
    // NOTE: producer and consumer expect to bind to the queue by reference:
    // 1) STL uses values, therefore plain queue argument will not work: wrap the queue into `std::ref` instead.
    // 2) Using `std::ref` is not normal: it is a red-flag for race conditions, which needs to be addressed by design.
    // In this case multiple threads share the queue which is supposed to be safe in multi-threaded (MT) environment.
    // NOTE: many successful test runs do not guarantee that the queue is MT-safe.
    // You may make your producers to work longer, try running optimized builds hoping to trigger an error,
    // or enable option(TSAN "Thread Sanitizer" ON) in the CMakeLists.txt
    // (remember to regenerate the cmake build by deleting the build directories).
    // Limitations:
    //  - clang++-13 does not ship std::jthread.
    //  - thread sanitizer is supported only on Linux and Apple Clang.
}