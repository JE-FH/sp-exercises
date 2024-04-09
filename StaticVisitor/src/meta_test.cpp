#include "meta.hpp"

#include <doctest/doctest.h>

#include <string>
#include <vector>
#include <set>
#include <map>
#include <cstdint>  // uint8_t

/** TODO: fix the meta library to satisfy the assertions below. */

/** is_bool_v tests: */
static_assert(is_bool_v<bool>, "bool is a bool");
static_assert(is_bool_v<bool&>, "reference to bool is a bool");
static_assert(is_bool_v<bool&&>, "rvalue reference to bool is a bool");
static_assert(is_bool_v<const bool>, "const bool is a bool");
static_assert(is_bool_v<const bool&>, "const reference to bool is a bool");
static_assert(is_bool_v<volatile bool>, "volatile bool is a bool");

// TODO: Uncomment
static_assert(!is_bool_v<bool*>, "pointer to bool is not a bool");
static_assert(!is_bool_v<bool[2]>, "bool array is not a bool");
static_assert(!is_bool_v<char>, "char is not a bool");
static_assert(!is_bool_v<int>, "int is not a bool");
static_assert(!is_bool_v<float>, "float is not a bool");
static_assert(!is_bool_v<double>, "double is not a bool");
static_assert(!is_bool_v<std::string>, "string is not a bool");
static_assert(!is_bool_v<std::vector<bool>>, "vector of bool is not a bool");


/** is_number_v tests: */
static_assert(is_number_v<uint8_t>, "uint8_t is a number");
static_assert(is_number_v<int8_t>, "int8_t is a number");
static_assert(is_number_v<int>, "int is a number");
static_assert(is_number_v<int&>, "reference to int is a number");
static_assert(is_number_v<int&&>, "rvalue reference to int is a number");
static_assert(is_number_v<const int>, "const int is a number");
static_assert(is_number_v<const int&>, "const int is a number");
static_assert(is_number_v<volatile int>, "volatile int is a number");
static_assert(is_number_v<long long>, "long long is a number");
static_assert(is_number_v<float>, "float is a number");
static_assert(is_number_v<double>, "double is a number");

// TODO: Uncomment
static_assert(!is_number_v<uint8_t*>, "pointer to uint8_t is not a number");
static_assert(!is_number_v<int*>, "pointer to int is not a number");
static_assert(!is_number_v<int[2]>, "array of int is not a number");
static_assert(!is_number_v<bool>, "bool is not a number");
static_assert(!is_number_v<std::string>, "string is not a number");
static_assert(!is_number_v<std::vector<int>>, "vector of int is not a number");


/** is_character_v tests: */
static_assert(is_character_v<char>, "char is a character");
static_assert(is_character_v<char&>, "reference to char is a character");
static_assert(is_character_v<char&&>, "rvalue reference to char is a character");
static_assert(is_character_v<const char>, "const char is a character");
static_assert(is_character_v<const char&>, "const reference to char is a character");
static_assert(is_character_v<volatile char>, "volatile char is a character");

// TODO: Uncomment
static_assert(!is_character_v<char[2]>, "array of char is not a character");
static_assert(!is_character_v<char*>, "pointer to char is not a character");
static_assert(!is_character_v<const char*>, "pointer to const char is not a character");
static_assert(!is_character_v<uint8_t>, "uint8_t is not a character");
static_assert(!is_character_v<int8_t>, "int8_t is not a character");
static_assert(!is_character_v<int>, "int is not a character");
static_assert(!is_character_v<float>, "float is not a character");
static_assert(!is_character_v<double>, "double is not a character");
static_assert(!is_character_v<std::string>, "string is not a character");
static_assert(!is_character_v<std::vector<char>>, "vector of char is not a character");


/** is_string_v tests: */
static_assert(is_string_v<std::string>, "string is a string");
static_assert(is_string_v<std::string&>, "reference to a string is a string");
static_assert(is_string_v<std::string&&>, "rvalue reference to a string is a string");
static_assert(is_string_v<const std::string>, "const string is a string");
static_assert(is_string_v<const std::string&>, "const string reference is a string");
static_assert(is_string_v<char*>, "mutable C string is a string");
static_assert(is_string_v<const char*>, "const C string is a string");
static_assert(is_string_v<const char* const>, "const const C string is a string");
static_assert(is_string_v<char[2]>, "array of char is a string");
static_assert(is_string_v<char[7]>, "array of char is a string");

// TODO: Uncomment
static_assert(!is_string_v<std::string[]>, "array of string is not a string");
static_assert(!is_string_v<char**>, "pointer to mutable C string is not a string");
static_assert(!is_string_v<int>, "int is not a string");
static_assert(!is_string_v<float>, "float is not a string");
static_assert(!is_string_v<double>, "double is not a string");
static_assert(!is_string_v<std::vector<char>>, "vector of char is not a string");


/** is_container_v tests: */
static_assert(is_container_v<std::vector<int>>, "vector of int is a container");
static_assert(is_container_v<std::vector<int>&>, "reference to vector of int is a container");
static_assert(is_container_v<std::vector<int>&&>, "rvalue reference to vector of int is a container");
static_assert(is_container_v<const std::vector<int>>, "const vector of int is a container");
static_assert(is_container_v<const std::vector<int>&>, "const reference of a vector of int is a container");
static_assert(is_container_v<std::vector<char>>, "vector of char is a container");
static_assert(is_container_v<std::vector<std::string>>, "vector of string is a container");
static_assert(is_container_v<std::initializer_list<int>>, "initializer list of int is a container");
static_assert(is_container_v<std::set<int>>, "set is a container");
static_assert(is_container_v<std::map<int, int>>, "map is a container");
static_assert(is_container_v<int[2]>, "array of int is a container");

// TODO: Uncomment
static_assert(!is_container_v<bool>, "bool is not a container");
static_assert(!is_container_v<char>, "char is not a container");
static_assert(!is_container_v<int>, "int is not a container");
static_assert(!is_container_v<float>, "float is not a container");
static_assert(!is_container_v<double>, "double is not a container");
static_assert(!is_container_v<int*>, "pointer to int is not a container");
static_assert(!is_container_v<std::string>, "string is not a container");

//tuple
static_assert(!is_tuple_v<std::vector<int>>, "vector of int  is not a tuple");
static_assert(!is_tuple_v<std::vector<char>>, "vector of char  is not a tuple");
static_assert(!is_tuple_v<std::vector<std::string>>, "vector of string  is not a tuple");
static_assert(!is_tuple_v<std::initializer_list<int>>, "initializer list of int  is not a tuple");
static_assert(!is_tuple_v<std::set<int>>, "set  is not a tuple");
static_assert(!is_tuple_v<std::map<int, int>>, "map  is not a tuple");
static_assert(!is_tuple_v<int[2]>, "array of int is not a tuple");
static_assert(!is_tuple_v<std::vector<std::tuple<std::tuple<int>, double, int, std::string>>>, "Vector of tuples is not a tuple");

static_assert(!is_tuple_v<bool>, "bool is not a tuple");
static_assert(!is_tuple_v<char>, "char is not a tuple");
static_assert(!is_tuple_v<int>, "int is not a tuple");
static_assert(!is_tuple_v<float>, "float is not a tuple");
static_assert(!is_tuple_v<double>, "double is not a tuple");
static_assert(!is_tuple_v<int*>, "pointer to int is not a tuple");
static_assert(!is_tuple_v<std::string>, "string is not a tuple");

static_assert(is_tuple_v<std::tuple<int>>, "Scalar tuple is a tuple");
static_assert(is_tuple_v<std::tuple<int, int, int, int>>, "N tuple is a tuple");
static_assert(is_tuple_v<std::tuple<std::tuple<int>, double, int, std::string>>, "N tuple is a tuple");

TEST_CASE("Tests for meta library are compile-time only") { CHECK(true); }