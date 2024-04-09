#pragma once
#include "op.hpp"
#include "AST.hpp"
#include "state.hpp"
#include <vector>
#include <string>


namespace calculator {
	class symbol_table_t;

	class symbol_table_t {
		std::vector<std::string> names; ///< stores the variable names
		std::vector<double> initial;    ///< stores the initial values of variables
	public:
		/// Creates a variable with given name and initial value
		[[nodiscard]] var_t var(std::string name, double init = 0) {
			auto res = names.size();
			names.push_back(std::move(name));
			initial.push_back(init);
			return var_t(res);
		}
		/// Creates a system state initialized with initial variable values
		[[nodiscard]] state_t state() const { return { initial }; }
	};
}