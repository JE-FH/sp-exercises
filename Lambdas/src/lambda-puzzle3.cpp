/**
 * Purpose: exercise lambda expressions with STL algorithms.
 * @author Marius Mikucionis <marius@cs.aau.dk>
 */
#include <doctest/doctest.h>
#include <iostream>
#include <vector>
#include <random>
#include <iterator>
#include <algorithm>
#include <string>
#include <numeric>
#include <sstream>

static auto gen = std::mt19937{std::random_device{}()};
static auto dist = std::uniform_int_distribution<int>{0, 100};

void fill_with_data(std::vector<int>& data, size_t count)
{
    std::generate_n(std::back_inserter(data), count, [&] { return dist(gen); });
}

template<typename T>
concept Streamable = requires(T s, std::ostream& os) {
    {os << s};
};

template <Streamable T>
 void print_data(std::ostream& os, const std::vector<T>& data)
{
    std::copy(std::cbegin(data), std::cend(data), std::ostream_iterator<T>(os, " "));
    os << '\n';
}

int compute_sum(const std::vector<int>& data)
{
    return std::accumulate(std::cbegin(data), std::cend(data), 0);
}

std::string concatenate(const std::vector<int>& data)
{
    return std::accumulate(std::cbegin(data), std::cend(data), std::string(),
                           [](std::string a, int b) { return a + std::to_string(b); });
}

size_t odd_count(const std::vector<int>& data)
{
    return std::count_if(std::cbegin(data), std::cend(data), [](int a) {return a % 2 == 1;});
}

std::vector<std::string> stringify(const std::vector<int>& data)
{
    auto res = std::vector<std::string>{};
    std::transform(std::cbegin(data), std::cend(data), std::back_inserter(res),
                          [](int a) { return std::to_string(a); });
    return res;
}

std::vector<std::string> compute_sorted(const std::vector<std::string>& data)
{
    auto res = data;
    std::sort(std::begin(res), std::end(res), [](const std::string& a, const std::string& b) {
        return a < b;
    });
    // sorting implementation of decreasing alphabetical order
    return res;
}

std::vector<int> squares(const std::vector<int>& n)
{
    auto res = std::vector<int>{};
    std::transform(std::cbegin(n), std::cend(n), std::back_inserter(res), [](int a) {return a*a;});
    // compute square of each input element
    return res;
}



TEST_CASE("Lambda puzzle3")
{
    SUBCASE("fill_with_data") {
        auto data = std::vector<int>{};
        fill_with_data(data, 20);
        CHECK(data.size() == 20);
    }
    SUBCASE("print_data") {
        std::ostringstream os;
        print_data(os, std::vector<int>{1, 2, 3, 4, 5, 6});
        CHECK(os.str() == "1 2 3 4 5 6 \n");
    }
    SUBCASE("compute_sum") {
        auto sum = compute_sum(std::vector<int>{1, 6, 2, 7});
        CHECK(sum == 16);
    }
    SUBCASE("concatenate") {
        auto combined = concatenate(std::vector<int>{1, 2, 3, 4});
        CHECK(combined == "1234");
    }
    SUBCASE("odd_count") { 
        auto c = odd_count(std::vector<int>{1, 2, 7, 3, 9, 4});
        CHECK(c == 4);
    }
    SUBCASE("stringify") {
        auto data_str = stringify(std::vector<int>{1, 2, 3, 4, 5});
        CHECK(data_str == std::vector<std::string>{"1", "2", "3", "4", "5"});
    }
    /** TODO: write test for compute_sorted */
    SUBCASE("computed_sorted") {
        auto unsorted = std::vector<std::string> { "a", "d", "t", "3", "1" };
        auto sorted_str = compute_sorted(unsorted);
        CHECK(sorted_str == std::vector<std::string>{"1", "3", "a", "d", "t"});
    }
    /** TODO: write test for squares */
    SUBCASE("squares") {
        auto s = squares(std::vector<int>{1, 2, 3, 4, 5, 8, 9});
        CHECK(s == std::vector<int>{1, 4, 9, 16, 25, 64, 81});
    }
    // make print_data a function template, so that the following is accepted:
    // print_data(std::cout, sorted_str);
    auto strvec = compute_sorted(stringify(std::vector<int>{743, 1, 784, 123, 87}));
    print_data(std::cout, strvec);
}
