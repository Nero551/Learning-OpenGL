cmake_minimum_required(VERSION 4.1.2)

set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_C_COMPILER /usr/bin/clang)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

project(Engine)

add_executable(Engine

    
    src/OpenGL.cpp
    src/Engine/Window.cpp
    src/FileSystem/FileSystem.cpp
    Libraries/lib/glad.c
)

add_subdirectory(src/Math)
add_subdirectory(src/Renderer)


find_package(glfw3 REQUIRED)

target_include_directories(Engine PRIVATE
    Libraries/include
)

target_link_libraries(Engine
    glfw
    GL
)
