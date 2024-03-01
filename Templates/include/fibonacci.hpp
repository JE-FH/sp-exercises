#ifndef TEMPLATES_FIBONACCI_HPP
#define TEMPLATES_FIBONACCI_HPP

#include <cstddef> // size_t

template <typename T = std::size_t>
T fib(std::size_t i)
{
	if (i < 2u)
		return T{1};
	else
		return fib<T>(i-1) + fib<T>(i-2);
}


#endif	// TEMPLATES_FIBONACCI_HPP
