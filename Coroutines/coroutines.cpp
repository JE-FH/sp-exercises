#include <coro/coro.hpp>
#include <ranges>
#include <iostream>
#include <iterator>
#include <source_location>
#include <hash_map>

void log(const std::string& msg, std::source_location loc = std::source_location::current())
{
    std::cout << msg << " in " << loc.function_name() << " at " << loc.file_name() << ':' << loc.line() << ':'
              << loc.column() << std::endl;
}

struct Counter
{
    struct iterator
    {
        Counter& ref;
        const size_t& operator*() const { return ref.state; }
        void operator++()
        {
            if (ref.state < ref.bound)
                ++ref.state;
        }
    };
    struct sentinel
    {
        bool operator==(const iterator& it) const { return it.ref.state == it.ref.bound; }
    };
    iterator begin() { return iterator{*this}; }
    sentinel end() const { return sentinel{}; }
    Counter(size_t first, size_t bound): state{first}, bound{bound} {}

private:
    size_t state;
    size_t bound;
};

void test_counter()
{
    log("===");
    auto n = Counter{1, 10};
    auto b = std::begin(n);
    for (auto i = 0; i < 6 && b != std::end(n); ++i, ++b)
        std::cout << *b << ' ';
    std::cout << '\n';
    for (auto i = 0; i < 6 && b != std::end(n); ++i, ++b)
        std::cout << *b << ' ';
    std::cout << '\n';
};

void test_iota()
{
    log("===");
    auto n = std::views::iota(0, 10);
    for (auto i : n)
        std::cout << i << ' ';
    std::cout << '\n';
}

coro::generator<size_t> ten()
{
    for (std::size_t i = 0; i < 10; ++i)
        co_yield i;
    co_return;
}

void test_ten()
{
    log("===");
    auto n = ten();
    for (auto i : n)
        std::cout << i << ' ';
    std::cout << '\n';
}

coro::generator<size_t> Naturals()
{
    std::size_t n = 0;
    while (true) {
        ++n;
        co_yield n;
    }
}

void test_Naturals()
{
    log("===");
    auto n = Naturals();
    for (auto i : n | std::views::take(5))
        std::cout << i << ' ';
    std::cout << '\n';
    for (auto i : n | std::views::take(5))
        std::cout << i << ' ';
    std::cout << '\n';
}

coro::generator<size_t> Fibonacci()
{
    std::size_t a = 0;
    std::size_t b = 1;
    while (true)
        co_yield std::exchange(a, std::exchange(b, a + b));
}

void test_Fibonacci()
{
    log("===");
    auto fib = Fibonacci();
    std::ranges::copy(fib | std::views::take(20), std::ostream_iterator<size_t>(std::cout, " "));
    std::cout << std::endl;
    std::ranges::copy(fib | std::views::take(10), std::ostream_iterator<size_t>(std::cout, " "));
    std::cout << std::endl;
}

coro::generator<std::size_t> Collatz(std::size_t current) {
    co_yield current;
    while (current > 1) {
        if (current % 2 == 0) {
            current = current / 2;
        } else {
            current = 3 * current + 1;
        }
        co_yield current;
    }
    co_return;
}

std::size_t CollatzLen(std::size_t number) {
    return std::ranges::distance(Collatz(number));
}

coro::generator<std::size_t> CollatzLens() {
    for (auto n : std::views::iota(0) | std::views::transform(CollatzLen)) {
        co_yield n;
    }
    co_return;
}

std::size_t MaxCollatz(std::size_t n)
{
    return std::ranges::max(std::views::iota((std::size_t)0, n) | std::views::transform(CollatzLen));
}

void test_Collatz()
{
    log("===");
    auto fib = Fibonacci();
    std::ranges::copy(Collatz(7), std::ostream_iterator<std::size_t>(std::cout, " "));
    std::cout << std::endl;
    std::ranges::copy(Collatz(0), std::ostream_iterator<std::size_t>(std::cout, " "));
    std::cout << std::endl;
    std::ranges::copy(Collatz(1), std::ostream_iterator<std::size_t>(std::cout, " "));
    std::cout << std::endl;
    std::ranges::copy(Collatz(200), std::ostream_iterator<std::size_t>(std::cout, " "));
    std::cout << std::endl;
    std::ranges::copy(CollatzLens() | std::views::take(20), std::ostream_iterator<std::size_t>(std::cout, " "));
    std::cout << std::endl;
    std::cout << "max 200: " << MaxCollatz(200) << std::endl;
}

int main()
{
    test_counter();
    test_iota();
    test_ten();
    test_Naturals();
    test_Fibonacci();
    test_Collatz();
    return 0;
}
