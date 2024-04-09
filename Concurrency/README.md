# Concurrency Exercises

## Thread-Protected Queue

Consider a queue class template for a producer-consumer problem:

1. Run benchmark [mtqueue_bm.cpp](tests/mtqueue_bm.cpp) in optimized **Release** configuration:
   1. Observe that **mtqueue** in [mtqueue.hpp](include/mtqueue.hpp) uses `std::list`, run `mtqueue_bm` and record the results. 
   2. Change **mtqueue** in [mtqueue.hpp](include/mtqueue.hpp) to use `std::deque` instead of `std::list`, rerun `mtqueue_bm` and record the results.
   3. Compare the benchmark results: which data structure is better for this use case? Why?
2. Solve `TODO` in [mtqueue.cpp](src/mtqueue.cpp):
   1. Create a shared queue of messages. 
   2. Create a producer which puts messages to the container.
   3. Create a consumer printing the messages to `std::cout`.
   4. Create multiple asynchronous producers.
   5. Verify the code against concurrency issues (run many threads for many data)
      - Linux/macOS: consult with `ThreadSanitizer` (add `-DTSAN=ON` to `cmake` configuration step).
      - Windows/MSVC: try [AppVerifier](https://learn.microsoft.com/en-us/windows-hardware/drivers/devtest/application-verifier)
6. Fix the "mtqueue" to ensure thread-safety in [mtqueue.hpp](include/mtqueue.hpp):
   1. Solve data race by using [mutual exclusion](https://en.cppreference.com/w/cpp/thread/mutex).
   2. Change `mtqueue::get` to always return a concrete value instead of `std::optional`. 
   3. Change `mtqueue::get` to block and wait until the queue is not empty, use [condition variable](https://en.cppreference.com/w/cpp/thread/condition_variable) to signal between threads.
   4. Check for concurrency issues 
   5. Rerun `mtqueue_bm` benchmark, record the results and compare with previous results.


## Futures and Promises

Implement `TODO` requirements in [future.cpp](src/futures.cpp).

## Monadic `and_then`

`std::future` lacks monadic member functions like `and_then` which would apply another function object on its future result when it becomes available. Instead, please provide a non-member function template `std::future<Res> and_then(std::future<T>&& input, Fn&& fn)`, which applies `fn` on the data from `input` asynchronously (on a different thread) and returns another `std::future` result.

Assume that `fn` returns `Res` when applied on `T` (see [`std::invoke_result_t`](https://en.cppreference.com/w/cpp/types/result_of)).

Implement and apply `and_then` in [futures.cpp](src/futures.cpp).

## Thread Pool

Implement a thread pool class template to pre-allocate a specified number of threads.

1. Constructor creates a number of threads waiting for tasks.
2. Use container (e.g. `std::queue`) of `std::function<void()>` to store tasks.
3. Use `std::mutex` and `std::condition_variable` to protect the task queue.
4. Destructor should notify all waiting threads to terminate and joins them.
5. Provide `async` method template similar to `std::async` to add tasks.
   - Use perfect capture or `std::tuple` to store function and arguments into lambda.
   - Use `std::promise` to return the value to a `std::future`.
   - Use `std::shared_ptr` to capture `std::promise` into lambda.
6. Test the thread pool with producers and consumers from the "Thread-Protected Queue" exercise above in [mtqueue.cpp](src/mtqueue.cpp).

