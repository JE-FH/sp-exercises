#pragma once
#include "op.hpp"
#include <vector>
#include <memory>
#include <string>

namespace calculator {
	using state_t = std::vector<double>;

	expr_t operator<<=(std::shared_ptr<var_t> v, std::shared_ptr<expr_t> e);

	class term_t {
	public:
		virtual ~term_t() noexcept = default;
		virtual double operator()(state_t&) = 0;
	};

	class expr_t {
	public:
		std::shared_ptr<term_t> term;

		expr_t(std::shared_ptr<term_t> term);
		expr_t(double c);
		double operator()(state_t&);

		friend expr_t operator+(expr_t lhs, expr_t rhs);
		friend expr_t operator-(expr_t lhs, expr_t rhs);
		friend expr_t operator*(expr_t lhs, expr_t rhs);
		friend expr_t operator/(expr_t lhs, expr_t rhs);

		expr_t& operator+=(expr_t t);
		expr_t& operator-=(expr_t t);
		expr_t& operator*=(expr_t t);
		expr_t& operator/=(expr_t t);
	};

	class const_t : public term_t {
		double _value;
	public:
		const_t(double c);
		double operator()(state_t&);
	};

	class var_t : public term_t {
		size_t _id;
		double& get_value(state_t& s);
	public:
		var_t(size_t id);
		double operator()(state_t&);
		double operator()(state_t&, double new_value);
		expr_t operator<<=(expr_t e);
	};

	class assign_t : public term_t {
		std::shared_ptr<var_t> _var;
		std::shared_ptr<term_t> _term;
		op_t _op;
	public:
		assign_t(std::shared_ptr<var_t> var, std::shared_ptr<term_t> term);
		double operator()(state_t&);
	};

	class unary_t : public term_t {
		std::shared_ptr<term_t> _term;
		op_t _op;
	public:
		double operator()(state_t&);
	};
	
	class binary_t : public term_t {
		std::shared_ptr<term_t> _term1;
		std::shared_ptr<term_t> _term2;
		op_t _op;
	public:
		binary_t(std::shared_ptr<term_t> lhs, std::shared_ptr<term_t> rhs, op_t op);
		double operator()(state_t&);
	};

	class symbol_table_t {
		std::vector<std::string> names; ///< stores the variable names
		std::vector<double> initial;    ///< stores the initial values of variables
	public:
		/// Creates a variable with given name and initial value
		[[nodiscard]] std::shared_ptr<var_t> var(std::string name, double init = 0) {
			auto res = names.size();
			names.push_back(std::move(name));
			initial.push_back(init);
			auto var = std::make_shared<var_t>();
			return ;
		}
		/// Creates a system state initialized with initial variable values
		[[nodiscard]] state_t state() const { return { initial }; }
	};

}