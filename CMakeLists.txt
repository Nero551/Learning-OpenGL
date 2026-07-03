cmake_minimum_required(VERSION 4.1.2)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")
set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-stdlib=libc++ -Wno-reserved-module-identifier")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

project(Engine LANGUAGES C CXX)
find_package(glfw3 REQUIRED)

add_executable(Engine)

target_sources(Engine
    PRIVATE
        src/main.cpp

    PUBLIC
    FILE_SET CXX_MODULES
    FILES
        src/math.ixx
)


target_include_directories(Engine PRIVATE
    Libraries/include
    src
)

target_link_libraries(Engine PRIVATE
    glfw
    GL
)

target_compile_options(Engine PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)