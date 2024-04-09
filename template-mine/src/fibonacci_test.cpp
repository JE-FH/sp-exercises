#include "fibonacci.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

template <int X>
struct Fib
{
	static constexpr int value = Fib<X - 2>::value + Fib<X - 1>::value;
};

template<>
struct Fib<0>
{
	static constexpr int value = 1;
};

template <>
struct Fib<1>
{
	static constexpr int value = 1;
};


TEST_CASE("Runtime Fibonacci")
{
	REQUIRE(fib(0) == 1u);
	REQUIRE(fib(1) == 1u);
	REQUIRE(fib(2) == 2u);
	REQUIRE(fib(3) == 3u);
	REQUIRE(fib(4) == 5u);
	REQUIRE(fib(5) == 8u);
	REQUIRE(fib(40) == 165580141u);
}

// TODO: uncomment and implement compile-time Fibonacci sequence
TEST_CASE("Compile-time Fibonacci")
{
	REQUIRE(Fib<0>::value == 1u);
	REQUIRE(Fib<1>::value == 1u);
	REQUIRE(Fib<2>::value == 2u);
	REQUIRE(Fib<3>::value == 3u);
	REQUIRE(Fib<4>::value == 5u);
	REQUIRE(Fib<5>::value == 8u);
	REQUIRE(Fib<40>::value == 165580141u);
}
