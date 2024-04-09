cmake_minimum_required(VERSION 3.15)
project(Lambdas CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(sanitizers.cmake)
include(doctest.cmake)
include(benchmark.cmake)

enable_testing()

add_subdirectory(src)