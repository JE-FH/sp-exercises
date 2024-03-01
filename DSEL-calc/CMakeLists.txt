# CMakeList.txt : CMake project for session-1, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (DSELCal "main.cpp" "expr.cpp" "op.hpp" "expr.hpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET session-1 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
