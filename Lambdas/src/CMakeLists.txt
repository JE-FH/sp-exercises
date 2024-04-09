add_executable(visitor visitor.cpp)

add_executable(lambda_puzzle1 lambda-puzzle1.cpp)
target_link_libraries(lambda_puzzle1 PRIVATE doctest::doctest_with_main)

add_executable(lambda_puzzle2 lambda-puzzle2.cpp)
target_link_libraries(lambda_puzzle2 PRIVATE doctest::doctest_with_main)

add_executable(lambda_puzzle3 lambda-puzzle3.cpp)
target_link_libraries(lambda_puzzle3 PRIVATE doctest::doctest_with_main)

add_executable(lambda_api lambda_api.cpp)
target_link_libraries(lambda_api PRIVATE benchmark::benchmark_main)
add_test(NAME lambda_api COMMAND lambda_api)

add_test(NAME visitor COMMAND visitor)
add_test(NAME lambda_puzzle1 COMMAND lambda_puzzle1)
add_test(NAME lambda_puzzle2 COMMAND lambda_puzzle2)
add_test(NAME lambda_puzzle3 COMMAND lambda_puzzle3)