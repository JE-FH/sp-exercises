#include "power.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

template <int X, int Y>
struct Divisor
{
	static constexpr int value = X % Y == 0 ? Y : Divisor<X, Y - 1>::value;
};

template <int X>
struct Divisor<X, 1>
{
	static constexpr int value = 1;
};

template <int X>
struct Divisor<X, 0>
{
	static constexpr int value = 1;
};

template<int X>
struct IsPrime {
	static constexpr bool value = Divisor<X,X - 1>::value == 1;
};

// TODO: implement Power template
TEST_CASE("Prime test")
{
	REQUIRE(IsPrime<1>::value == true);
	REQUIRE(IsPrime<2>::value == true);
	REQUIRE(IsPrime<3>::value == true);
	REQUIRE(IsPrime<4>::value == false);
	REQUIRE(IsPrime<5>::value == true);
	REQUIRE(IsPrime<6>::value == false);
	REQUIRE(IsPrime<7>::value == true);
	REQUIRE(IsPrime<8>::value == false);
	REQUIRE(IsPrime<9>::value == false);
	REQUIRE(IsPrime<10>::value == false);
	REQUIRE(IsPrime<11>::value == true);
	REQUIRE(IsPrime<12>::value == false);
}
