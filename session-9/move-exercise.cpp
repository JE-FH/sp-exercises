#include "../StaticVisitor/include/meta.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include "impl.hpp"

std::vector<int> make_data(int from, std::size_t size) {
    auto res = std::vector<int>(size);
    std::iota(std::begin(res), std::end(res), from);
    return res;
}

/**
 * TODO: Implement a variadic function template "sum" taking arbitrary number of container of int arguments
         and returning the total sum of their elements. Final solution is ~5 lines.
 * Proposed plan (uncomment the corresponding test cases as you progress):
 * 1) Implement a function "sum" with one argument of type std::vector<int> returning int, see std::accumulate.
 * 2) Refactor the function "sum" into a function template, which assumes that the argument is some container of int.
 *    Template type-checking is not required for this step, keep it simple.
 * 3) Add a function template "sum" overload taking two arguments (containers of int) and
      returns the sum over the elements of both containers.
 * 4) Generalize the function templates to accept both: lvalues and rvalues (there are two ways).
 * 5) Generalize both function templates into one variadic function template taking arbitrary number of arguments.
 *    Use parameter pack and fold expression.
 * 6) Use your meta.hpp library from StaticVisitor exercise to type-check that the arguments are indeed containers.
 */

TEST_CASE("Perfect forwarding") {
    const auto d1 = make_data(1, 10);
    auto d2 = make_data(11, 10);
    SUBCASE("1,2) one argument") {
        auto s = sum(d1);
        CHECK(s == (1 + 10) * 10 / 2);
    }
    SUBCASE("3) two lvalue arguments") {
        auto s = sum(d1, d2);
        CHECK(s == (1 + 20) * 20 / 2);
    }
    SUBCASE("4) lvalue and rvalue") {
        auto s1 = sum(make_data(1, 10));
        CHECK(s1 == (1 + 10) * 10 / 2);
        auto s2 = sum(d1, make_data(11, 10));
        CHECK(s2 == (1 + 20) * 20 / 2);
    }
    SUBCASE("5) three arguments") {
        auto s = sum(d1, d2, make_data(21, 10));
        CHECK(s == (1 + 30) * 30 / 2);
    }
    SUBCASE("5) four arguments") {
        auto s = sum(d1, make_data(21, 10), d2, make_data(31, 10));
        CHECK(s == (1 + 40) * 40 / 2);
    }
    SUBCASE("5) zero arguments") {
        auto s = sum();
        CHECK(s == 0);
    }
    /* // Compilation should fail with a meaningful error message
    SUBCASE("6) type-check the container") {
        auto s = sum(50);
    }*/
    
}

/**
 * TODO: Implement lazy function evaluation by capturing the function and its arguments and executing the function later.
 *       Final solution is about 4+5=9 lines.
 * Proposed plan (uncomment the corresponding test cases):
 * 1) Implement a function object "summation" (struct with call operator()) which computes a sum over arbitrary
 *    number of containers of int. You may reuse/call the function template "sum" developed above.
 * 2) Implement a generic function template "lazy" taking an arbitrary function object and one container,
 *    returning a function with zero parameters by applying the given function on the given container.
 *    Use either std::bind (easy) or a lambda expression (advanced).
 * 3) Generalize the "lazy" function template into variadic function template taking arbitrary
 *    number of containers of int.
 * 4) Optimize the generic "lazy" function to pass the arguments by their corresponding rvalue/lvalue type.
 * 5) Check the types passed to "lazy": check that the function can accept/bind to given the argument types.
 *    Use std::is_invocable.
 */



TEST_CASE("Lazy evaluation") {
    const auto d1 = make_data(1, 10);
    auto d2 = make_data(11, 10);
    
    SUBCASE("1) summation") {
        auto sum_fn = summation{};
        CHECK(sum_fn(d1) == (1 + 10) * 10 / 2);               // function object call
        CHECK(sum_fn(make_data(1, 10)) == (1 + 10) * 10 / 2);  // function object call
    }
    SUBCASE("2) one argument lazy evaluation") {
        auto lazy_sum = lazy(summation{}, d1); // capture the arguments
        CHECK(lazy_sum() == (1 + 10) * 10 / 2);      // call/evaluate later
    }
    SUBCASE("3) two arguments") {
        auto lazy_sum = lazy(summation{}, d1, d2);
        CHECK(lazy_sum() == (1 + 20) * 20 / 2);
    }

    SUBCASE("3) three arguments") {
        auto lazy_sum = lazy(summation{}, d1, d2, make_data(21, 10));
        CHECK(lazy_sum() == (1 + 30) * 30 / 2);
    }
    SUBCASE("3) four arguments") {
        auto lazy_sum = lazy(summation{}, d1, make_data(21, 10), d2, make_data(31, 10));
        CHECK(lazy_sum() == (1 + 40) * 40 / 2);
    }
    SUBCASE("3) zero arguments") {
        auto lazy_sum = lazy(summation{});
        CHECK(lazy_sum() == 0);
    }
    
    /* // compilation fails with perfect forwarding, but succeed with alternative,
       // can we replace perfect forwarding with something else?
    SUBCASE("3) lazy call to sum") { // need to specify the argument type, not nice:
        auto sum_fn = std::bind(sum<std::vector<int>>, d1); // capture the arguments
        CHECK(sum_fn() == (1+10)*10/2);                     // call/evaluate later
    }
    */
    SUBCASE("4) move support") {
        CHECK(d1.size() == 10);
        CHECK(d2.size() == 10);
        auto lazy_sum = lazy(summation{}, std::move(d1), std::move(d2));
        CHECK(d1.size() == 10); // not moved (why?)
        CHECK(d2.empty());      // moved (where is the data now?)
        CHECK(lazy_sum() == (1 + 20) * 20 / 2);
        CHECK(lazy_sum() == (1 + 20) * 20 / 2); // the second call should still evaluate to the same value
    }
    
    /* // compilation should fail with a meaningful message
    SUBCASE("5) type-check the container") {
        auto lazy_sum = lazy(summation{}, 50);
    }
    */
}