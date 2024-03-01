add_executable(kindof_test kindof_test.cpp)

add_executable(type_name_test type_name_test.cpp)

add_executable(deduction deduction.cpp)

add_executable(fibonacci_test fibonacci_test.cpp)

add_executable(power_test power_test.cpp)

if (Boost_FOUND)
    add_executable(type_name_boost type_name_boost.cpp)
    add_test(NAME type_name_boost COMMAND type_name_boost)
endif(Boost_FOUND)

add_test(NAME kindof_test COMMAND kindof_test)
add_test(NAME type_name_test COMMAND type_name_test)
add_test(NAME fibonacci_test COMMAND fibonacci_test)
add_test(NAME power_test COMMAND power_test)
