# Ranges and Coroutines

## Instructions:
0. Make sure the project builds and tests pass:
```shell
cmake -B build
cmake --build build
ctest --test-dir build
```
1. Inspect examples in [coroutines.cpp](coroutines.cpp), 
2. Create a [Collatz](https://en.wikipedia.org/wiki/Collatz_conjecture) sequence generator coroutine for a given positive starting number. 
For example, the following is the sequence starting with 7:
`7 22 11 34 17 52 26 13 40 20 10 5 16 8 4 2 1`. Collatz sequence is empty for `0`. Use these facts in your unit tests.
3. Given a positive number, estimate the length of Collatz sequence. 
4. Create another coroutine generating an infinite sequence of lengths of Collatz sequences starting with 0, 1, 2, and so on. For example, the first 10 numbers: `0 1 2 8 3 6 9 17 4 20`.
5. Compute the maximal length of Collatz sequences for starting numbers of up to 100.
6. If time permits, add [memoization](https://en.wikipedia.org/wiki/Memoization) to Collatz length coroutine.

## Hints:
[generator](https://en.cppreference.com/w/cpp/coroutine/generator) (use `coro::generator` if `std::generator` is not available)

[take](https://en.cppreference.com/w/cpp/ranges/take_view)
[distance](https://en.cppreference.com/w/cpp/iterator/ranges/distance),
[max](https://en.cppreference.com/w/cpp/algorithm/ranges/max)
