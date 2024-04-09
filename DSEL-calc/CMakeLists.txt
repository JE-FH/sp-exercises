# CMakeList.txt : CMake project for session-1, include source and define
# project specific logic here.
#

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_SHARED_LIBS OFF)

include(sanitizers.cmake)
include(doctest.cmake)

# Add source to this project's executable.
add_executable(calculator_test "calculator_test.cpp" "calculator.cpp")
target_link_libraries(calculator_test PRIVATE doctest::doctest_with_main)

enable_testing()
add_test(NAME calculator_test COMMAND calculator_test)

# TODO: Add tests and install targets if needed.
