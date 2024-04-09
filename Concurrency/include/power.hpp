#ifndef TEMPLATES_POWER_HPP
#define TEMPLATES_POWER_HPP

#include <cstddef> // size_t

template <typename T>
constexpr T power(T number, std::size_t p)
{
	if (number == 0)
		return 0;
	else if (p == 0)
		return 1;
	else if (p == 1)
		return number;
	auto res = power(number, p/2);
	res *= res;
	if (p % 2 == 1)
		res *= number;
	return res;
}

/** function object template for specific power value */
template <std::size_t P, bool Odd = P%2> // primary declaration for even powers
struct Power
{
	template <typename T>
	constexpr T operator()(T x) {
		auto res = Power<P/2>{}(x);
		return res * res;
	}
};

template <std::size_t P>
struct Power<P,true> // specialization for odd powers
{
	template <typename T>
	constexpr T operator()(T x) {
		auto res = Power<P/2>{}(x);
		return res * res * x;
	}
};

template <>
struct Power<1,true> // specialization for power of 1
{
	template <typename T>
	constexpr T operator()(T x) { return x; }
};

template <>
struct Power<0,false> // specialization for power of 0
{
	template <typename T>
	constexpr T operator()(T x) { return 1; }
};

/** meta-function for computing compile-time powers */
template <typename T, T N, std::size_t P, bool Odd = P%2>
struct power_t
{
	static constexpr auto value = power_t<T,N,P/2>::value * power_t<T,N,P/2>::value;
};

template <typename T, T N, std::size_t P>
struct power_t<T,N,P,true>
{
	using value_type = T;
	static constexpr auto value = power_t<T,N,P/2>::value * power_t<T,N,P/2>::value * N;
};

template <typename T, T N>
struct power_t<T,N,1,true>
{
	using value_type = T;
	static constexpr auto value = N;
};

template <typename T, T N>
struct power_t<T,N,0,false>
{
	using value_type = T;
	static constexpr auto value = T{1};
};

template <typename T, T N, std::size_t P>
constexpr auto power_v = power_t<T,N,P>::value;

#endif	// TEMPLATES_POWER_HPP
