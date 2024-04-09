# Static Visitor for JSON input/output

Motivation: we often want to serialize and load data from our datastructures with as little overhead and maintenance as possible, thus a generic solution is preferred. There are many libraries for performing reflection over generic data structures, but they are often intrusive and C++ standard still does not have a solution. Instead of reflection, we can use the static visitor pattern to provide low level access to data members. Static visitor uses compile-time polymorphism, it does not rely on central inheritance, adding support is trivial and it does not penalize runtime if unused.

JSON format is chosen as it is very popular among many modern frameworks.

The library consists of:
- Meta predicates for checking the basic types that JSON supports (bool, number, text, array/container, object).
- Customizing adapters wrapping input/output streams: `json_ostream` and `json_istream`.
- Output and input operators coupling `json_iostream`s with JSON data types.
- User-defined types (`struct`s and `class`es) need to have `accept` member function template calling arbitrary visitor with the content of their member fields.
- `json_writer_t` and `json_reader_t` implement the visitor pattern with member function templates `visit(std::string name, Value value)` to handle individual fields with given `name` and `value`. In principle, `json_writer_t` functionality can be part of `json_ostream` adapter, but they are separated here in order to separate visitor implementation from I/O operations.

Proposed plan:

1. Focus on one unit test section at a time and implement one feature at a time.
2. Start with [meta_test.cpp](src/meta_test.cpp): uncomment static assertions and implement the corresponding meta predicates until all assertions pass.
3. Implement the output functionality completely first ([json_output.hpp](include/json_output.hpp)) to satisfy tests in [json_output_test.cpp](src/json_output_test.cpp).

4. Compare `json_writer_t` and `printer` visitor developed for DSEL calculator during previous extended exercise.

5. Implement the input support ([json_input.hpp](include/json_input.hpp), similar to [json_output.hpp](include/json_output.hpp)) to satisfy tests in [json_input_test.cpp](src/json_input_test.cpp).

6. If time permits, extend the library to support `std::tuple` types: add a meta predicate to check if the type is created using `std::tuple` template, add a unit test for tuple output, implement tuple output using variadic function templates (either recursion or [tag-dispatch](https://en.cppreference.com/w/cpp/utility/integer_sequence) and [fold expressions](https://en.cppreference.com/w/cpp/language/fold)). Reuse as much as possible (e.g. call `json_writer_t::visit` method for each element in the tuple).
   For example, given `auto t = std::make_tuple(3,3.14,"pi");` then `json_ostream{std::cout} << t;` should produce `{"1":3,"2":3.14,"3":"pi"}`.