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

include(CTest)
include(Catch)
catch_discover_tests(mlp-cpp-test)
