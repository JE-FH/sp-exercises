/**
 * Functions and meta-functions for generating compile-time tables.
 * Author: Marius Mikucionis <marius@cs.aau.dk>
 */
#ifndef TEMPLATES_TABLES_HPP
#define TEMPLATES_TABLES_HPP

#include <array>
#include <cstddef> // size_t

template <typename Fn, std::size_t...Is>
constexpr auto fn_table(Fn&& fn, std::index_sequence<Is...>)
{
	return std::array<std::invoke_result_t<Fn,std::size_t>, sizeof...(Is)> { fn(Is)... };
}

template <template <std::size_t> class MetaFn, std::size_t...Is>
constexpr auto meta_table(std::index_sequence<Is...>)
{
	return std::array<typename MetaFn<0u>::value_type, sizeof...(Is)> { MetaFn<Is>::value... };
}

template <template <typename T, std::size_t> class MetaFn, typename T, std::size_t...Is>
constexpr auto meta_table1(std::index_sequence<Is...>)
{
	return std::array<typename MetaFn<T,0u>::value_type, sizeof...(Is)> { MetaFn<T,Is>::value... };
}


#endif	// TEMPLATES_TABLES_HPP
