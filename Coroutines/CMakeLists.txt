cmake_minimum_required(VERSION 3.15)
project(Coroutines)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(sanitizers.cmake)
include(doctest.cmake)
include(libcoro.cmake)

enable_testing()

add_executable(coroutines coroutines.cpp)
target_link_libraries(coroutines PRIVATE libcoro)
add_test(NAME coroutines COMMAND coroutines)

set_property(TARGET coroutines PROPERTY CXX_STANDARD 23)
