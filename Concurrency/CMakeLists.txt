cmake_minimum_required(VERSION 3.15)
project(concurrency CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(sanitizers.cmake)
include(doctest.cmake)
include(benchmark.cmake)

find_package(OpenMP)
include(CheckIncludeFileCXX)
check_include_file_cxx("parallel/algorithm" HAVE_GNU_PARALLEL)
if(OPENMP_FOUND AND HAVE_GNU_PARALLEL)
  message(STATUS "OpenMP with GNU parallel found, very good!")
else()
  message(STATUS "OpenMP/GNU parallel NOT found, stringsort3_bm will not work.")
endif()

find_package(TBB QUIET)
if(TBB_FOUND)
  message(STATUS "ThreadBuildingBlocks found, very good!")
else()
  message(STATUS "ThreadBuildingBlocks NOT found, stringsort4_bm will not work.")
  message(STATUS "Consider installing libtbb-dev or similar from your package manager")
endif()

find_package(Threads REQUIRED)

include_directories(include)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
