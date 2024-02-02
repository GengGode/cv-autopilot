include(cmake/cmake_env.cmake)

cmake_minimum_required(VERSION 3.15)
project(autopilot)
set(BUILD_TESTS OFF CACHE BOOL "Build tests")
set(BUILD_EXAMPLES OFF CACHE BOOL "Build examples")
set(BUILD_TESTS ON)

set(inface_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(inface_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

add_subdirectory(source)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()