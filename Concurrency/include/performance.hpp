/** Utilities to optimize performance */
#ifndef CONCURRENCY_PERFORMANCE_HPP
#define CONCURRENCY_PERFORMANCE_HPP


// C++20 uses attributes: https://en.cppreference.com/w/cpp/language/attributes/likely
#if defined(__GNUC__) && __GNUC__ >= 4
#define LIKELY(x)   (__builtin_expect((x), 1))
#define UNLIKELY(x) (__builtin_expect((x), 0))
#else
#define LIKELY(x)   (x)
#define UNLIKELY(x) (x)
#endif

/**
 * https://youtu.be/vrfYLlR8X8k?t=3521
 * Speed hierarchy:
 * - comparisons
 * - (u)int add, subtract, bit-ops, shift
 * - FP add, subtract
 * - (u)int multiply, FP multiply
 * - FP division, remainder
 * - (u)int division, remainder
 * Do not waste time on replacing n/=2 with n>>=1
 */

#endif /* CONCURRENCY_PERFORMANCE_HPP */
