/**
 * Exercise for lecture on templates and type deduction.
 * The purpose is to get acquainted with template specialization.
 * Author: Marius Mikucionis <marius@cs.aau.dk>
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include <vector>
#include <string>

/**
 * Type Displayer template declaration without an implementation:
 * when invoked, it forces the compiler to issue an error and reveal the type argument.
 * Useful in compile-time type-debugging.
 */
template <typename T>
struct TD;

/** TODO: implement a template class kind_t which takes one type parameter and
 * has a static member function to_string() computing a string representation of the given parameter type kind.
 * Handle the following type kinds and corresponding strings:
 * - "type": plain value type (class type or fundamental type like int)
 * - "pointer": some kind of pointer type
 * - "C string": for a C character string
 * - "C++ string": for std::string
 */


template <typename T>
struct kind_t {
	constexpr static std::string to_string() {
		if (std::is_same_v<std::remove_cv_t<T>, std::string>) {
			return "C++ string";
		} else if (std::is_same_v<std::remove_cv_t<T>, char*> || std::is_same_v<std::remove_cv_t<T>, const char*>) {
			return "C string";
		} else if (std::is_pointer_v<std::remove_cv_t<T>>) {
			return "pointer";
		} else {
			return "type";
		}
	}
};


/** The interface template function calling the kind_t template class */
// TODO: uncomment to enable kind_of function template:
template <typename T>
std::string kind_of(T value) {
	//TD<std::remove_cv_t<decltype(value)>> v_type; // type displayer reveals the type of value variable
	return kind_t<decltype(value)>::to_string();
}

using namespace std;
using namespace std::string_literals; // ""s operator converting string literals into C++ string

TEST_CASE("Type kinds")
{
    auto v1 = 5;
    auto v2 = 3.141;
    auto v3 = "hello C";
    auto v4 = "hello C++"s;
    auto v5 = string("C++");
    auto v6 = new int(7);
    auto v7 = new char[11];
    auto v8 = vector<int>();
// TODO: uncomment to enable tests
	CHECK(kind_of(v1)=="type");
	CHECK(kind_of(v2)=="type");
	CHECK(kind_of(v3)=="C string");
	CHECK(kind_of(v4)=="C++ string");
	CHECK(kind_of(v5)=="C++ string");
	CHECK(kind_of(v6)=="pointer");
	CHECK(kind_of(v7)=="C string");
	CHECK(kind_of(v8)=="type");

	delete v6;
	delete [] v7;
}
