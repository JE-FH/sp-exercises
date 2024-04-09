#include "expr.hpp"
#include <stdexcept>
#include <memory>
namespace calculator {
	double expr_t::operator()(state_t& s) {
		return (*term)(s);
	}

	double& var_t::get_value(state_t& s) {
		if (_id < s.size()) {
			return s[_id];
		} else {
			throw std::exception("var id is out of range");
		}
	}

	double var_t::operator()(state_t& s) {
		return get_value(s);
	}

	double var_t::operator()(state_t& s, double new_value) {
		return get_value(s) = new_value;
	}

	double assign_t::operator()(state_t& s) {
		auto value = (*term)(s);
		return _var(s, value);
	}

	double unary_t::operator()(state_t& s) {
		auto value = (*term)(s);
		switch (_op) {
		case op_t::plus:
			return value;
		case op_t::minus:
			return -value;
		default:
			throw std::logic_error("Invalid operation");
		}
	}

	double binary_t::operator()(state_t& s) {
		auto lhs = (*_term1)(s);
		auto rhs = (*_term2)(s);
		switch (_op) {
		case op_t::plus:
			return lhs + rhs;
		case op_t::minus:
			return lhs - rhs;
		case op_t::div:
			if (rhs == 0) {
				throw std::logic_error("division by zero");
			}
			return lhs / rhs;
		case op_t::mul:
			return lhs * rhs;
		default:
			throw std::logic_error("Invalid operation");
		}
	}

	expr_t operator+(expr_t lhs, expr_t rhs) {
		return expr_t(std::make_shared<binary_t>(std::move(lhs.term), std::move(rhs.term), op_t::plus));
	}

	expr_t operator-(expr_t lhs, expr_t rhs) {
		return expr_t(std::make_shared<binary_t>(std::move(lhs.term), std::move(rhs.term), op_t::minus));
	}

	expr_t operator*(expr_t lhs, expr_t rhs) {
		return expr_t(std::make_shared<binary_t>(std::move(lhs.term), std::move(rhs.term), op_t::mul));
	}

	expr_t operator/(expr_t lhs, expr_t rhs) {
		return expr_t(std::make_shared<binary_t>(std::move(lhs.term), std::move(rhs.term), op_t::div));
	}

	expr_t operator-(expr_t e) {
		return expr_t(std::make_shared<unary_t>(std::move(e.term), op_t::minus));
	}

	expr_t operator+(expr_t e) {
		return expr_t(std::make_shared<unary_t>(std::move(e.term), op_t::plus));
	}

	expr_t operator<<=(expr_t lhs, expr_t rhs) {
		auto var = std::dynamic_pointer_cast<var_t>(std::move(lhs.term));
		if (var == nullptr) {
			throw std::logic_error("assignment destination must be a variable expression");
		}
		return expr_t(std::make_shared<assign_t>(*var, std::move(rhs.term)));
	}

	expr_t operator+=(expr_t v, expr_t e) {
		return v <<= v + std::move(e);
	}

	expr_t operator-=(expr_t v, expr_t e) {
		return v <<= v - std::move(e);
	}

	expr_t operator*=(expr_t v, expr_t e) {
		return v <<= v * std::move(e);
	}

	expr_t operator/=(expr_t v, expr_t e) {
		return v <<= v / std::move(e);
	}
}
