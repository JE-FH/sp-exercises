/**
 * Various ways computing the number of decimal digits
 * Based on "Writing Fast Code" by Andrei Alexandrescu, code::dive 2015.
 * https://youtu.be/vrfYLlR8X8k
 */
#ifndef INCLUDE_DIGITS_HPP
#define INCLUDE_DIGITS_HPP

#include "power.hpp"
#include "tables.hpp"
#include "performance.hpp"
#include <array>
#include <limits>
#include <cmath> // log

/** computes the number of decimal digits in number using division */
template <typename T>
T digits10_div(T number)
{
	auto res = T{0};
	do {
		++res;
		number /= 10;
	} while (number);
	return res;
}

/** computes the number of decimal digits in number using logarithm */
template <typename T>
T digits10_log(T number)
{
	if constexpr (std::numeric_limits<T>::is_signed) {
		if (number == std::numeric_limits<T>::min())
			return std::numeric_limits<T>::digits10 + 1;
		if (number < 0)
			number = -number;
	}
	if (number < 10)
		return 1;
	if (number == std::numeric_limits<T>::max())
		return std::numeric_limits<T>::digits10+1;
	return T(std::ceil(std::log10(number+1)));
}

/** computes the number of decimal digits in number using multiplication */
template <typename T>
T digits10_mul(T number)
{
	if constexpr (std::numeric_limits<T>::is_signed) {
		if (number == std::numeric_limits<T>::min())
			return std::numeric_limits<T>::digits10 + 1;
		if (number < 0)
			number = -number;
	}
	constexpr auto largest = power(T{10}, std::numeric_limits<T>::digits10);
	if (number >= largest)
		return std::numeric_limits<T>::digits10+1;
	auto n = T{10};
	auto res = T{1};
	for (;;) {
		if (LIKELY(number < n))
			return res;
		++res;
		n *= 10;
	}
}

/** computes the number of decimal digits in number using fewer divisions */
template <typename T>
T digits10_div2(T number)
{
	if constexpr (std::numeric_limits<T>::is_signed) {
		if (number == std::numeric_limits<T>::min())
			return std::numeric_limits<T>::digits10 + 1;
		if (number < 0)
			number = -number;
	}
	auto res = T{0};
	for (;;) { // infinite loop and break ASAP
		if (LIKELY(number < 10))
			return res+1;
		if (LIKELY(number < 100))
			return res+2;
		res += 2;
		number /= 100;
	}
}

/** computes the number of decimal digits in number using fewer divisions */
template <typename T>
T digits10_div3(T number)
{
	if constexpr (std::numeric_limits<T>::is_signed) {
		if (number == std::numeric_limits<T>::min())
			return std::numeric_limits<T>::digits10 + 1;
		if (number < 0)
			number = -number;
	}
	auto res = T{0};
	for (;;) { // infinite loop and break ASAP
		if (LIKELY(number < 10))
			return res+1;
		if (LIKELY(number < 100))
			return res+2;
		if (LIKELY(number < 1000))
			return res+3;
		res += 3;
		number /= 1000;
	}
}

/** computes the number of decimal digits in number using fewer divisions */
template <typename T>
T digits10_div4(T number)
{
	if constexpr (std::numeric_limits<T>::is_signed) {
		if (number == std::numeric_limits<T>::min())
			return std::numeric_limits<T>::digits10 + 1;
		if (number < 0)
			number = -number;
	}
	auto res = T{0};
	for (;;) { // infinite loop and break ASAP
		if (LIKELY(number < 10))
			return res+1;
		if (LIKELY(number < 100))
			return res+2;
		if (LIKELY(number < 1000))
			return res+3;
		if constexpr (std::numeric_limits<T>::max() >= 1000) {
			if (LIKELY(number < 10000))
				return res + 4;
			res += 4;
			number /= 10000;
		}
	}
}

/** computes the number of decimal digits in number using fewer divisions */
template <typename T>
T digits10_div5(T number)
{
	if constexpr (std::numeric_limits<T>::is_signed) {
		if (number == std::numeric_limits<T>::min())
			return std::numeric_limits<T>::digits10 + 1;
		if (number < 0)
			number = -number;
	}
	auto res = T{0};
	for (;;) { // infinite loop and break ASAP
		if (LIKELY(number < 10))
			return res+1;
		if (LIKELY(number < 100))
			return res+2;
		if (LIKELY(number < 1000))
			return res+3;
		if constexpr (std::numeric_limits<T>::max() >= 1000) {
			if (LIKELY(number < 10000))
				return res + 4;
			if (LIKELY(number < 100000))
				return res + 5;
			res += 5;
			number /= 100000;
		}
	}
}

/** computes the number of decimal digits in number using fewer divisions */
template <typename T>
T digits10_div6(T number)
{
	if constexpr (std::numeric_limits<T>::is_signed) {
		if (number == std::numeric_limits<T>::min())
			return std::numeric_limits<T>::digits10 + 1;
		if (number < 0)
			number = -number;
	}
	auto res = T{0};
	for (;;) { // infinite loop and break ASAP
		if (LIKELY(number < 10))
			return res+1;
		if (LIKELY(number < 100))
			return res+2;
		if (LIKELY(number < 1000))
			return res+3;
		if constexpr (std::numeric_limits<T>::max() >= 1000) {
			if (LIKELY(number < 10000))
				return res + 4;
			if (LIKELY(number < 100000))
				return res + 5;
			if (LIKELY(number < 1000000))
				return res + 6;
			res += 6;
			number /= 1000000;
		}
	}
}

/** computes the number of decimal digits in number using fewer divisions */
template <typename T>
T digits10_divn(T number)
{
	if constexpr (std::numeric_limits<T>::is_signed) {
		if (number == std::numeric_limits<T>::min())
			return std::numeric_limits<T>::digits10 + 1;
		if (number < 0)
			number = -number;
	}
	auto res = T{0};
	for (;;) { // infinite loop and break ASAP
		if (LIKELY(number < 10))
			return res+1;
		if (LIKELY(number < 100))
			return res+2;
		if (LIKELY(number < 1000))
			return res + 3;
		if constexpr (std::numeric_limits<T>::max() >= 1000) {
			if (LIKELY(number < 10000))
				return res + 4;
			if (LIKELY(number < 100000))
				return res + 5;
			if constexpr (std::numeric_limits<T>::max() >= 100000) {
				if (LIKELY(number < 1000000))
					return res + 6;
				if (LIKELY(number < 10000000))
					return res + 7;
				res += 7;
				number /= 10000000;
			}
		}
	}
}

template <typename T>
constexpr T power10(std::size_t p)
{
	return power(T{10}, p);
}

template <typename T>
constexpr auto power10_table()
{
	auto p10 = [](std::size_t p) { return power(T{10}, p); };
	return fn_table(p10, std::make_index_sequence<std::numeric_limits<T>::digits10+1>{});
}

template <typename T, std::size_t P>
using power10_t = power_t<T,10,P>;

template <typename T>
constexpr auto power10_meta_table()
{
	return meta_table1<power10_t,T>(std::make_index_sequence<std::numeric_limits<T>::digits10+1>{});
}

/** computes the number of decimal digits in number using loop through power table */
template <typename T>
T digits10_loop(T number)
{
	if constexpr (std::numeric_limits<T>::is_signed) {
		if (number == std::numeric_limits<T>::min())
			return std::numeric_limits<T>::digits10 + 1;
		if (number < 0)
			number = -number;
	}
	constexpr auto powers = power10_meta_table<T>();
	auto i = 1u;
	while (i < powers.size()) {
		if (LIKELY(number < powers[i]))
			return i;
		++i;
	}
	return i;
}


#endif /* INCLUDE_DIGITS_HPP */
