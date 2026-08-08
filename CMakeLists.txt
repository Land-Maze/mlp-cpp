cmake_minimum_required(VERSION 4.0)

project(mlp-cpp
    VERSION 0.1.0
    DESCRIPTION "Multilayer Perceptron C++ Library and Executable"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(mlp_cpp main.cpp ${SOURCES})

target_include_directories(mlp_cpp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(mlp_cpp PRIVATE /W4)
else()
    target_compile_options(mlp_cpp PRIVATE -Wall -Wextra -Wpedantic)
endif()
