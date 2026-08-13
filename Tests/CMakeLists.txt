cmake_minimum_required(VERSION 4.1.2)
project(UnitTests)

file(GLOB_RECURSE ENGINE_SOURCES
        ../src/Utilities/*.cpp
)

file(GLOB_RECURSE TEST_SOURCES
        MathTests/*.cpp
)

add_executable(UnitTests
        ${ENGINE_SOURCES}
        ${TEST_SOURCES}
)

set_target_properties(UnitTests PROPERTIES UNITY_BUILD ON)
target_precompile_headers(UnitTests PRIVATE
        "$<$<COMPILE_LANGUAGE:CXX>:../src/pch.hpp>"
)

target_include_directories(UnitTests PRIVATE
        ../src
)

find_package(Catch2 CONFIG REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)
target_link_libraries(UnitTests PRIVATE
        Catch2::Catch2WithMain
        glfw
        glad::glad
)

target_compile_options(UnitTests PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)