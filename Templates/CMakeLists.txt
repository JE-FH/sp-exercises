cmake_minimum_required(VERSION 3.15)
project(templates CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # for clang-tidy

option(ASAN "Address Sanitizer" OFF)

# turn on the warnings:
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wpedantic -Wall -Wextra)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4)
endif()

if (ASAN)
    if (UNIX)
        # Linux/Mac: GCC/Clang/Apple_Clang have the same options
        add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
        add_link_options(-fsanitize=address)
    elseif(WIN32)
        if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
            add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
            add_link_options(-fsanitize=address)
            message(STATUS "Address sanitizer is probably not supported by GCC/Clang on Windows")
        elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
            add_compile_options(/fsanitize=address)
            add_link_options(/fsanitize=address)
        endif()
    endif()
endif()

#set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "~/.local/lib/cmake/benchmark")
#find_package(benchmark REQUIRED)

find_package(Boost 1.67 QUIET COMPONENTS headers)

include_directories(include)

enable_testing()

add_subdirectory(src)
