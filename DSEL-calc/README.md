# DSEL Calculator

## Purpose:
1) Revisit the [operator overloading](https://people.cs.aau.dk/~marius/Teaching/SP2024/classes.html#/3/22), exercise PImpl and dynamic polymorphism.
2) Introduce a small Domain Specific Embedded Language (DSEL) modeling a lazy calculator.


## Suggested Workflow
0) Before changing anything, run `calculator_test` first and see if the project works, 
   then create/uncomment a test case in [calculator_test.cpp](calculator_test.cpp),
   (see a brief introduction to *doctest* in **Unit Testing** section below).
1) Implement multiplication and division operators by following the examples of addition and subtraction in [calculator.hpp](calculator.hpp).
2) **Refactor** the `expr_t` code into a hierarchy of possible Abstract Syntax Tree (AST) **term**s (independent of expression operators), e.g.: 

![class diagram](calculator.png)

3) Refactor the adapter **struct expr_t** which wraps **term**s and builds the corresponding Abstract Syntax Tree through operator overloading.
4) Implement support for constant expressions (values like `5` and `3.14`).
5) Implement support for printing (use unit testing!), e.g.:
```cpp
   std::cout << printer{sys, a+b} << std::endl; // prints "a+b"
```

## Questions for Reflections
1) Compare the signatures of binary operators in this project with [std::valarray operator overloads](https://en.cppreference.com/w/cpp/numeric/valarray/operator_arith3):
   do they take arguments by value or by reference? return by value or by reference?
   Are there a fundamental differences in semantics (meaning/implementation)?
2) Did you use inheritance or aggregation or both? where? why?
3) Did you use smart pointers? which? where? why?
4) Can we change `unique_ptr` into `shared_ptr` or vice-a-versa? why?
5) Which definitions can we safely hide into separate **cpp** file without disturbing the test cases? 
6) Did you like unit testing? Would you use it in your future projects?

## Unit Testing
This exercise introduces [doctest](https://github.com/doctest/doctest) unit testing framework.

It is a very simple, yet rich and powerful unit testing framework packed just in one header file.

For now, here is a list of the most important concepts:

1) Test case starts with a `TEST_CASE` macro taking a name as a parameter.
2) The body contains statements just like any C/C++ function.
3) The body should include one or more test statements:
   * `REQUIRE`: test if the condition is true and abort the test case otherwise.
   * `CHECK`: test if condition is true and proceed regardless.
   * `CHECK_THROWS_MESSAGE`: test that the expression produces an exception with a given message.
4) The body may contain a nested `SUBCASE` which continue the test case,
   except each `SUBCASE` is independent of its siblings, i.e. the shared test prefix is repeated 
   for each `SUBCASE` branch as if there was no other `SUBCASE`.
```cpp
TEST_CASE("The name or even better: the purpose of this test") {
    // body of the test
    auto os = std::ostringstream{};
    REQUIRE(2+3 == 5); // cannot proceed if arithmetics fail
    os << "hello";    
    CHECK(os.str() == "hello"); // you get what you put in
    CHECK_THROWS_MESSAGE(fn("naughty argument"), "error: someone is being naughty");
    SUBCASE("Extra functionality") {
        os << " world!"; // continue putting-in
        CHECK(os.str() == "hello world!");
    }
    SUBCASE("Alternative scenario") {
        os << " to you too"; // continue putting-in as if previous SUBCASE never happened
        CHECK(os.str() == "hello to you too");
    }
}
```
More details can be found in [doctest tutorial](https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md).
