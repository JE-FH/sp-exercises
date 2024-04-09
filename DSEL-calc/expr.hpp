#pragma once
#include "op.hpp"
#include "term.hpp"
#include "symbol_table.hpp"
#include "AST.hpp"
#include <vector>
#include <memory>
#include <string>

namespace calculator {
	class expr_t {
	public:
		std::shared_ptr<term_t> term;
		expr_t(const var_t& var)
			: term(std::make_shared<var_t>(var)) {};
		expr_t(std::shared_ptr<term_t> term)
			: term(std::move(term)) { }
		expr_t(double c)
			: term(std::make_shared<const_t>(c)) {}
		expr_t(const expr_t&) = default;
		expr_t(expr_t&&) = default;
		expr_t& operator=(const expr_t&) = default;
		expr_t& operator=(expr_t&&) = default;
		double operator()(state_t&);
	};

	expr_t operator-(expr_t e);
	expr_t operator+(expr_t e);

	expr_t operator+(expr_t lhs, expr_t rhs);
	expr_t operator-(expr_t lhs, expr_t rhs);
	expr_t operator*(expr_t lhs, expr_t rhs);
	expr_t operator/(expr_t lhs, expr_t rhs);

	expr_t operator<<=(expr_t v, expr_t e);
	expr_t operator+=(expr_t v, expr_t e);
	expr_t operator-=(expr_t v, expr_t e);
	expr_t operator*=(expr_t v, expr_t e);
	expr_t operator/=(expr_t v, expr_t e);
}