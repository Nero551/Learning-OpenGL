cmake_minimum_required(VERSION 4.1.2)

set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_C_COMPILER_LAUNCHER ccache)
set(CMAKE_CXX_COMPILER_LAUNCHER ccache)

project(UnitTests)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif ()

include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0
)

FetchContent_MakeAvailable(Catch2)

file(GLOB_RECURSE ENGINE_SOURCES
        ../src/Utilities/*.cpp
)

file(GLOB_RECURSE TEST_SOURCES
        MathTests/*.cpp
)

add_executable(UnitTests
        ../External/lib/glad.c
        ${ENGINE_SOURCES}
        ${TEST_SOURCES}
)


find_package(glfw3 REQUIRED)
set_target_properties(UnitTests PROPERTIES UNITY_BUILD ON)
target_precompile_headers(UnitTests PRIVATE
        "$<$<COMPILE_LANGUAGE:CXX>:../src/pch.hpp>"
)

target_include_directories(UnitTests PRIVATE
        ../External/include
        ../src
)


target_link_libraries(UnitTests PRIVATE
        Catch2::Catch2WithMain
        glfw
        GL
)

target_compile_options(UnitTests PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)