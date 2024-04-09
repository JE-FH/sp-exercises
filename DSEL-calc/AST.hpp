#pragma once
#include <memory>
#include "op.hpp"
#include "state.hpp"
#include "term.hpp"
namespace calculator {
	class symbol_table_t;
	class expr_t;
	class var_t : public term_t {
		size_t _id;
		double& get_value(state_t& s);
		var_t(size_t id)
			: _id(id) {}
	public:
		var_t(const var_t&) = default;
		var_t(var_t&&) = default;
		var_t& operator=(const var_t&) = default;
		var_t& operator=(var_t&&) = default;

		double operator()(state_t&);
		double operator()(state_t&, double new_value);
		friend class symbol_table_t;
	};

	class const_t : public term_t {
		double _value;
	public:
		const_t(double c)
			: _value(c) {}
		double operator()(state_t&) { return _value; }
	};

	class assign_t : public term_t {
		var_t _var;
		std::shared_ptr<term_t> term;
	public:
		assign_t(var_t var, std::shared_ptr<term_t> term)
			: _var(std::move(var)), term(std::move(term)) {}
		double operator()(state_t&);
	};

	class unary_t : public term_t {
		std::shared_ptr<term_t> term;
		op_t _op;
	public:
		unary_t(std::shared_ptr<term_t> term, op_t op)
			: term(std::move(term)), _op(op) {}
		double operator()(state_t& s);
	};

	class binary_t : public term_t {
		std::shared_ptr<term_t> _term1;
		std::shared_ptr<term_t> _term2;
		op_t _op;
	public:
		binary_t(std::shared_ptr<term_t> lhs, std::shared_ptr<term_t> rhs, op_t op)
			: _term1(std::move(lhs)), _term2(std::move(rhs)), _op(op) {}
		double operator()(state_t&);
	};
}