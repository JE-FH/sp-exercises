# Downloads and compiles DocTest unit testing framework
include(FetchContent)
set(FETCHCONTENT_QUIET ON)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

set(LIBCORO_EXTERNAL_DEPENDENCIES OFF CACHE BOOL "Use Cmake find_package to resolve dependencies instead of embedded libraries, Default=OFF.")
set(LIBCORO_BUILD_TESTS           OFF CACHE BOOL "Build the tests, Default=ON.")
set(LIBCORO_CODE_COVERAGE         OFF CACHE BOOL "Enable code coverage, tests must also be enabled, Default=OFF")
set(LIBCORO_BUILD_EXAMPLES        OFF CACHE BOOL "Build the examples, Default=ON.")
set(LIBCORO_RUN_GITCONFIG         OFF CACHE BOOL "Set the githooks directory to auto format and update the readme, Default=OFF.")
set(LIBCORO_BUILD_SHARED_LIBS     OFF CACHE BOOL "Build shared libraries, Default=OFF.")

set(LIBCORO_FEATURE_NETWORKING    OFF CACHE BOOL "Include networking features, Default=ON.")
set(LIBCORO_FEATURE_TLS           OFF CACHE BOOL "Include TLS encryption features, Default=ON.")

FetchContent_Declare(libcoro
        GIT_REPOSITORY https://github.com/jbaldwin/libcoro.git
        GIT_TAG v0.11.1   # "main" for latest
        GIT_SHALLOW TRUE  # download specific revision only (git clone --depth 1)
        GIT_PROGRESS TRUE # show download progress in Ninja
        USES_TERMINAL_DOWNLOAD TRUE)
FetchContent_MakeAvailable(libcoro)
