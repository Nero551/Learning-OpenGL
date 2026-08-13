cmake_minimum_required(VERSION 4.1.2)

set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_C_COMPILER_LAUNCHER ccache)
set(CMAKE_CXX_COMPILER_LAUNCHER ccache)

project(Nova)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif ()


add_executable(Nova
        src/Main.cpp
)

set_target_properties(Nova PROPERTIES UNITY_BUILD ON)

target_precompile_headers(Nova PRIVATE
        "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/src/pch.hpp>"
)
add_subdirectory(src/Core)
add_subdirectory(src/Utilities)
add_subdirectory(src/Modules)
add_subdirectory(src/World)

target_include_directories(Nova PRIVATE
        src
)

find_package(glad REQUIRED)
find_package(glfw3 REQUIRED)
find_package(assimp REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(magic_enum REQUIRED)
target_link_libraries(Nova
        PRIVATE
        glfw
        assimp::assimp
        glad::glad
        nlohmann_json::nlohmann_json
)
target_compile_options(Nova PRIVATE
        -Wall
        #        -Wextra
        #        -Wpedantic
)