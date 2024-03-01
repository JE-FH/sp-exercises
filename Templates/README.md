# Template Exercises

## Tasks

1. Open [kindof_test.cpp](src/kindof_test.cpp):
   - Follow the TODO comments and uncomment tests
   - Compile and run it, observe all tests fail
   - Follow the TODO comments and implement kind_t template
   - Recompile and run it again, observer the test pass
   - Fix the kind_t template as necessary for the tests to pass.

2. Open [type_name_test.cpp](src/type_name_test.cpp):
   - Compile and run it, observe all tests fail
   - Fix the test by entering the names of respective types
   - Recompile and run, observe tests passing.
   - Inspect how type_name is implemented in [type_name.hpp](include/type_name.hpp)
   - Extra: uncomment type_name test against Boost in [CMakeLists.txt](CMakeLists.txt)
   - Extra: inspect [type_name_boost.cpp](src/type_name_boost.cpp) how to use Boost implementation

3. Implement compile-time Fibonacci sequence [fibonacci.hpp](include/fibonacci.hpp)
    - benchmark against run-time implementation of Fibonacci function
    - Extra: Implement compile-time table for Fibonacci sequence (tip: use std::make_index_sequence)

4. Implement compile-time Power by integer meta-function [power.hpp](include/power.hpp)
    - benchmark against runtime power function implementation
    - benchmark against [std::pow](https://en.cppreference.com/w/cpp/numeric/math/pow)

5. Extra: Implement compile-time prime factorization
    - Implement compile-time integer square-root
    - Implement compile-time prime check
