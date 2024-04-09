#include "power.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("Integer power")
{
	REQUIRE(power(2, 0)==1);
	REQUIRE(power(2, 1)==2);
	REQUIRE(power(2, 2)==4);
	REQUIRE(power(2, 3)==8);
	REQUIRE(power(5, 5)==3125);
}

/** TODO: implement Power template
TEST_CASE("Integer power")
{
	REQUIRE(Power<2, 2>::value == 4);
	REQUIRE(Power<2, 3>::value == 8);
	REQUIRE(Power<5, 5>::value == 3125);
}
*/
