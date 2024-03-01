cmake_minimum_required(VERSION 3.15)
project(Extended1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_SHARED_LIBS OFF)

include(sanitizers.cmake)
include(doctest.cmake)
include(benchmark.cmake)

enable_testing()

add_executable(extended1_main main.cpp number_series.cpp number_series.hpp)
add_test(NAME extended1_main COMMAND extended1_template_main)

add_executable(number_series_test number_series_test.cpp number_series.cpp number_series.hpp)
target_link_libraries(number_series_test PRIVATE doctest::doctest_with_main)
add_test(NAME number_series_test COMMAND number_series_test)

add_executable(sort_bm sort_bm.cpp)
target_link_libraries(sort_bm PRIVATE benchmark::benchmark_main)
add_test(NAME sort_bm COMMAND sort_bm)

add_executable(number_series_bm number_series_bm.cpp number_series.cpp number_series.hpp)
target_link_libraries(number_series_bm PRIVATE benchmark::benchmark_main)
add_test(NAME number_series_bm COMMAND number_series_bm)
