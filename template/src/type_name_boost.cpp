/**
 * Tests the pretty printing type names against boost implementation
 * Author: Marius Mikucionis <marius@cs.aau.dk>
 */
#include "type_name.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <boost/type_index.hpp>
#include <functional>
#include <iostream>

template <typename T>
void print_size()
{
	std::cout << std::to_string(sizeof(T)) + "\t" + type_name<T>() << std::endl;
}

template <typename T>
void test()
{
	REQUIRE(type_name<T>() == boost::typeindex::type_id_with_cvr<T>().pretty_name());
	REQUIRE(type_name<const T>() == boost::typeindex::type_id_with_cvr<const T>().pretty_name());
	REQUIRE(type_name<volatile T>() ==
			boost::typeindex::type_id_with_cvr<volatile T>().pretty_name());
	REQUIRE(type_name<T&>() == boost::typeindex::type_id_with_cvr<T&>().pretty_name());
	REQUIRE(type_name<T&&>() == boost::typeindex::type_id_with_cvr<T&&>().pretty_name());
	REQUIRE(type_name<const T&>() == boost::typeindex::type_id_with_cvr<const T&>().pretty_name());
	REQUIRE(type_name<volatile T&>() ==
			boost::typeindex::type_id_with_cvr<volatile T&>().pretty_name());
}

TEST_CASE("type_name against boost")
{
	int	 ints1[] = { 1, 2, 3, 4, 5 };
	auto ints2	 = { 1, 2, 3, 4, 5 };
	auto x		 = 1.618033f;
	auto str	 = "hello";
	volatile int& (*f)(const int&);

	test<int>();
	test<size_t>();
	test<double>();
	test<decltype(ints1)>();
	test<decltype(ints2)>();
	test<decltype(x)>();
	test<decltype(str)>();
	test<std::string>();
	test<decltype(f)>();
	test<std::function<double(const int&)>>();
	test<decltype(print_size<size_t>)>();
}
