cmake_minimum_required(VERSION 3.15)
project(templates CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # for clang-tidy

include(sanitizers.cmake)

find_package(Boost 1.67 QUIET COMPONENTS headers)

include_directories(include)

enable_testing()

add_subdirectory(src)
