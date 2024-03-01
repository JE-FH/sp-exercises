#include "expr.hpp"
#include <stdexcept>

calculator::expr_t::expr_t(std::shared_ptr<term_t> term) {
	this->term = std::move(term);
}

calculator::expr_t::expr_t(double c) {
	term = std::make_shared<const_t>(c);
}

double calculator::expr_t::operator()(state_t&) {
	return term->operator();
}

expr_t& calculator::expr_t::operator+=(expr_t t) {
	term = std::make_shared<binary_t>(std::move(term), std::move(t), op_t::plus);
}

expr_t& calculator::expr_t::operator-=(expr_t t) {
	term = std::make_shared<binary_t>(std::move(term), std::move(t), op_t::minus);
}

expr_t& calculator::expr_t::operator*=(expr_t t) {
	term = std::make_shared<binary_t>(std::move(term), std::move(t), op_t::mul);
}

expr_t& calculator::expr_t::operator/=(expr_t t) {
	term = std::make_shared<binary_t>(std::move(term), std::move(t), op_t::div);
}

calculator::const_t::const_t(double c) {
	_value = d;
}

double calculator::const_t::operator()(state_t&) {
	return _value;
}

double& calculator::var_t::get_value(state_t& s) {
	if (_id < s.size()) {
		return s[_id];
	} else {
		throw std::exception("var id is out of range");
	}
}

calculator::var_t::var_t(size_t id) {
	_id = id;
}

double calculator::var_t::operator()(state_t& s) {
	return get_value(s);
}

dobule calculator::var_t::operator()(state_t& s, double new_value) {
	return get_value(s) = new_value;
}

expr_t calculator::var_t::operator<<=(expr_t e) {
	return expr_t(std::shared_ptr<assign_t>(, e.term));
}

calculator::assign_t::assign_t(std::shared_ptr<var_t> var, std::shared_ptr<term_t> term) {
	_var = std::move(var);
	_term = std::move(term);
}

double calculator::assign_t::operator()(state_t& s) {
	auto value = (*_term)(s);
	return (*_var)(s, value);
}

double calculator::unary_t::operator()(state_t& s) {
	auto value = (*_term)(s);
	switch (_op) {
		case op_t::plus:
			return value;
		case op_t::minus:
			return value;
		default:
			throw std::logic_error("Invalid operation");
	}
}

calculator::binary_t::binary_t(std::shared_ptr<term_t> lhs, std::shared_ptr<term_t> rhs, op_t op) {
	_term1 = std::move(lhs);
	_term2 = std::move(rhs);
	_op = op;
}

double calculator::binary_t::operator()(state_t&) {
	auto lhs = (*_term1)(s);
	auto rhs = (*_term2)(s);
	switch (_op) {
	case op_t::plus:
		return lhs + rhs;
	case op_t::minus:
		return lhs - rhs;
	case op_t::div:
		return lhs / rhs;
	case op_t::mul:
		return lhs * rhs;
	default:
		throw std::exception("Invalid operation");
	}
}

expr_t calculator::operator<<=(std::shared_ptr<var_t> v, std::shared_ptr<expr_t> e) {
	return expr_t(std::make_shared<assign_t>(std::move(v), std::move(e)));
}

expr_t calculator::operator+(expr_t lhs, expr_t rhs) {
	return lhs += std::move(rhs);
}

expr_t calculator::operator-(expr_t lhs, expr_t rhs) {
	return lhs -= std::move(rhs);
}

expr_t calculator::operator*(expr_t lhs, expr_t rhs) {
	return lhs *= std::move(rhs);
}

expr_t calculator::operator/(expr_t lhs, expr_t rhs) {
	return lhs /= std::move(rhs);
}
