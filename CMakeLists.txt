cmake_minimum_required(VERSION 4.1.2)

set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_C_COMPILER_LAUNCHER ccache)
set(CMAKE_CXX_COMPILER_LAUNCHER ccache)

project(Engine)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif ()


add_executable(Engine
        External/lib/glad.c
        src/Main.cpp
)

find_package(glfw3 REQUIRED)
find_package(assimp CONFIG REQUIRED)
set_target_properties(Engine PROPERTIES UNITY_BUILD ON)

target_precompile_headers(Engine PRIVATE
        "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/src/pch.hpp>"
)
add_subdirectory(src/Core)
add_subdirectory(src/Utilities)
add_subdirectory(src/Modules)
add_subdirectory(src/World)

target_include_directories(Engine PRIVATE
        External/include
        src
)

target_link_libraries(Engine
        glfw
        GL
        assimp::assimp
)

target_compile_options(Engine PRIVATE
        -Wall
        #        -Wextra
        #        -Wpedantic
)