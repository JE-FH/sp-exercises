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
		res = type_name<decltype(v1)>() == "int";
		CHECK(res);
		res = type_name<decltype(v2)>() == "double";
		CHECK(res);
		res = type_name<decltype(v3)>() == "char const*";
		CHECK(res);
		CHECK(type_name<decltype(v4)>() != "std::string<char>");  // OK to cheat here, because
		CHECK(type_name<decltype(v5)>() != "std::string<char>");  // implementation specific
		res = type_name<decltype(v6)>() == "int*";
		CHECK(res);
		res = type_name<decltype(v7)>() == "char*";
		CHECK(res);
		CHECK(type_name<decltype(v8)>() != "std::vector<int>");	 // implementation specific
	}
	SUBCASE("hand-crafted")
	{
		bool res;
		res = type_name<size_t>() == "unsigned long";
		CHECK(res);
		res = type_name<int>() == "int";
		CHECK(res);
		res = type_name<long>() == "long";
		CHECK(res);
		res = type_name<long int>() == "long";
		CHECK(res);
		res = type_name<long long>() == "long long";
		CHECK(res);
		res = type_name<const int>() == "int const";
		CHECK(res);
		res = type_name<const int&>() == "int const&";
		CHECK(res);
		res = type_name<volatile int&>() == "int volatile&";
		CHECK(res);
		res = type_name<volatile int&&>() == "int volatile&&";
		CHECK(res);
		res = type_name<const volatile int&&>() == "int const volatile&&";
		CHECK(res);
		res = type_name<decltype(ints1)>() == "int [5]";
		CHECK(res);
		res = type_name<decltype(ints2)>() == "std::initializer_list<int>";
		CHECK(res);
		res = type_name<decltype(str)>() == "char const*";
		CHECK(res);
		res = type_name<decltype(x)>() == "float";
		CHECK(res);
		res = type_name<std::string>() != "std::string";  // implementation specific
		CHECK(res);
		res = type_name<std::string_view>() != "std::string_view";	// implementation specific
		CHECK(res);
		res = type_name<decltype(f)>() == "int volatile& (*)(int const&)";
		CHECK(res);
		res = type_name<std::function<const char*(const int&)>>() ==
			"std::function<char const* (int const&)>";
		CHECK(res);
		res = type_name<std::function<double(const int&)>>() ==
			"std::function<double (int const&)>";
		CHECK(res);
		res = type_name<decltype(&print_size<size_t>)>() == "void (*)()";
		CHECK(res);
	}
}
