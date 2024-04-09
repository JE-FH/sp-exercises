# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("sP")

# Include sub-projects.
add_subdirectory ("session-1")
add_subdirectory ("session-3")
add_subdirectory ("session-4")
add_subdirectory ("session-7")
add_subdirectory ("session-9")
add_subdirectory("extended1-template")
add_subdirectory("DSEL-calc")
# add_subdirectory("template-mine")
add_subdirectory("template")
add_subdirectory("StaticVisitor")
add_subdirectory("test")
add_subdirectory("Lambdas")
add_subdirectory("Concurrency")
add_subdirectory("coroutines")
