#pragma once
#include "../StaticVisitor/include/meta.hpp"
#include <algorithm>
#include <functional>

template<ContainerC... Ts>
int sum(const Ts&... containers) {
	return (std::accumulate(std::cbegin(containers), std::cend(containers), 0) + ... + 0);
}

struct summation {
	template<ContainerC... Ts>
	int operator()(Ts&&... containers) const {
		return sum(std::forward<Ts>(containers)...);
	}
};

template<typename Tfo, ContainerC... Tc> 
	requires std::is_invocable_v<Tfo, Tc...>
auto lazy(Tfo f, Tc&&... c) {
	return std::bind(f, std::forward<Tc>(c)...);
}
