#pragma once
#include "state.hpp"
namespace calculator {
	class term_t {
	public:
		virtual ~term_t() noexcept = default;
		virtual double operator()(state_t&) = 0;
	};
}