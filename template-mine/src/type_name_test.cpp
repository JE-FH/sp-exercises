/**
 * Tests for pretty printing RTTI type names
 * Author: Marius Mikucionis <marius@cs.aau.dk>
 */
#include "type_name.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <functional>
#include <iostream>

template <typename T>
void print_size()
{
	std::cout << std::to_string(sizeof(T)) + "\t" + type_name<T>() << std::endl;
}

TEST_CASE("type_name")
{
	int	 ints1[] = { 1, 2, 3, 4, 5 };
	auto ints2	 = { 1, 2, 3, 4, 5 };
	auto x		 = 1.618033f;
	auto str	 = "hello";
	volatile int& (*f)(const int&);

	SUBCASE("auto test")
	{
		using namespace std;
		using namespace std::string_literals;  // "hello"s
		auto v1 = 5;
		auto v2 = 3.141;
		auto v3 = "hello C";
		auto v4 = "hello C++"s;
		auto v5 = string("C++");
		auto v6 = new int(7);
		auto v7 = new char[11];
		auto v8 = vector<int>();
		bool res;
		res = type_name<decltype(v1)>() == ""; // TODO: insert the type name
		CHECK(res);
		res = type_name<decltype(v2)>() == ""; // TODO: insert the type name
		CHECK(res);
		res = type_name<decltype(v3)>() == ""; // TODO: insert the type name
		CHECK(res);
		CHECK(type_name<decltype(v4)>() == "std::string"); // RTTI gives implementation specific type
		CHECK(type_name<decltype(v5)>() == "std::string"); // RTTI gives implementation specific type
		res = type_name<decltype(v6)>() == ""; // TODO: insert the type name
		CHECK(res);
		res = type_name<decltype(v7)>() == ""; // TODO: insert the type name
		CHECK(res);
		CHECK(type_name<decltype(v8)>() == "std::vector<int>"); // RTTI gives very detailed type
	}
	SUBCASE("hand-crafted")
	{
		bool res;
		res = type_name<size_t>() == ""; // TODO: insert the type name
		CHECK(res);
		res = type_name<int>() == ""; // TODO: insert the type name
		CHECK(res);
		res = type_name<long>() == ""; // TODO: insert the type name
		CHECK(res);
		res = type_name<long int>() == ""; // TODO: insert the type name
		CHECK(res);
		res = type_name<long long>() == ""; // TODO: insert the type name
		CHECK(res);
		res = type_name<const int>() == ""; // TODO: insert the type name
		CHECK(res);
		res = type_name<const int&>() == ""; // TODO: insert the type name
		CHECK(res);
		res = type_name<volatile int&>() == ""; // TODO: insert the type name
		CHECK(res);
		res = type_name<volatile int&&>() == ""; // TODO: insert the type name
		CHECK(res);
		res = type_name<const volatile int&&>() == ""; // TODO: insert the type name
		CHECK(res);
		res = type_name<decltype(ints1)>() == ""; // TODO: insert the type name
		CHECK(res);
		res = type_name<decltype(ints2)>() == ""; // TODO: insert the type name
		CHECK(res);
		res = type_name<decltype(str)>() == ""; // TODO: insert the type name
		CHECK(res);
		res = type_name<decltype(x)>() == ""; // TODO: insert the type name
		CHECK(res);
		CHECK(type_name<std::string>() == "std::string"); // RTTI gives implementation specific type
		CHECK(type_name<std::string_view>() == "std::string_view"); // RTTI gives very detailed type
		res = type_name<decltype(f)>() == ""; // TODO: insert the type name
		CHECK(res);
		res = type_name<std::function<const char*(const int&)>>() == ""; // TODO: insert the type name
		CHECK(res);
		res = type_name<std::function<double(const int&)>>() == ""; // TODO: insert the type name
		CHECK(res);
		res = type_name<decltype(&print_size<size_t>)>() == ""; // TODO: insert the type name
		CHECK(res);
	}
}
