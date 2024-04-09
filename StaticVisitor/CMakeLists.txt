project(static_visitor CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(sanitizers.cmake)
include(doctest.cmake)

include_directories(include)

enable_testing()

add_subdirectory(src)