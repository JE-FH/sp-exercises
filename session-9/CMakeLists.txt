# CMakeList.txt : CMake project for session-1, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (session-9_test "move-exercise.cpp" )
set_property(TARGET session-9_test PROPERTY CXX_STANDARD 20)
include(sanitizers.cmake)
include(doctest.cmake)
enable_testing()

target_link_libraries(session-9_test PRIVATE doctest::doctest_with_main)

add_test(NAME session-9_test COMMAND session-9_test)
# TODO: Add tests and install targets if needed.
