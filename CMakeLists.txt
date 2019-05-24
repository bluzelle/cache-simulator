cmake_minimum_required(VERSION 3.10)

project(cache_simulator CXX)

# ensure type is set
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

message("Build version ${PROJECT_VERSION}")

# use ccache if available...
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

# output dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

# compiler options...
set(CMAKE_CXX_STANDARD 17)
add_compile_options("-fdiagnostics-color=auto")

add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)

# todo: remove -Wno-implicit-fallthrough once CI moves past gcc 7.4.0...
set(warnings "-Wno-deprecated-declarations -Wall -Wextra -Werror -Wpedantic -Wno-implicit-fallthrough")
if (APPLE)
    set(warnings "${warnings} -Wno-extended-offsetof")
endif(APPLE)

set(CMAKE_CXX_FLAGS ${warnings})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(sim)
