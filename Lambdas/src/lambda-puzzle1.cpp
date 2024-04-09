/**
 * Purpose: debug lambda expressions.
 * @author Marius Mikucionis <marius@cs.aau.dk>
 */
#include <doctest/doctest.h>
#include <iostream>
#include <sstream>  // stringstream
#include <vector>
#include <functional>  // function
#include <algorithm>   // all_of

using filters_t = std::vector<std::function<bool(int)>>;

void add_divisor_filter(filters_t& container, int divisor)
{
    container.emplace_back([divisor](int value) { return value % divisor == 0; });
}

TEST_CASE("divisors")
{
    auto filters = filters_t{};
    add_divisor_filter(filters, 3);
    add_divisor_filter(filters, 5);

    auto os = std::ostringstream{};
    for (auto i = 0; i < 100; ++i) {
        if (std::all_of(std::begin(filters), std::end(filters), [&](auto& f) { return f(i); })) {
            os << i << " ";
        }
    }
    CHECK(os.str() == "0 15 30 45 60 75 90 ");
}
