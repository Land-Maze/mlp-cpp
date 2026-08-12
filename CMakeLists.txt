cmake_minimum_required(VERSION 3.16)

project(mlp-cpp
    VERSION 0.1.0
    DESCRIPTION "Multilayer Perceptron C++ Library"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

if(IS_MULTI_CONFIG)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo;MinSizeRel" CACHE STRING "Supported build configurations" FORCE)
else()
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build (Debug, Release, RelWithDebInfo, MinSizeRel)." FORCE)
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
    endif()
endif()

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.5.2
)
FetchContent_MakeAvailable(Catch2)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")

add_executable(mlp-cpp-test ${TEST_SOURCES} ${SOURCES})

target_link_libraries(mlp-cpp-test
    PRIVATE
        Catch2::Catch2WithMain
)

target_include_directories(mlp-cpp-test
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(mlp-cpp-test PRIVATE /W4)
else()
    target_compile_options(mlp-cpp-test PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(mlp-cpp-example example/main.cpp ${SOURCES})

target_include_directories(mlp-cpp-example
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(mlp-cpp-example PRIVATE /W4)
else()
    target_compile_options(mlp-cpp-example PRIVATE -Wall -Wextra -Wpedantic)
endif()

include(CTest)
include(Catch)
catch_discover_tests(mlp-cpp-test)
