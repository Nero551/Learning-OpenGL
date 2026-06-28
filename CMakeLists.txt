cmake_minimum_required(VERSION 4.1.2)

set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_C_COMPILER /usr/bin/clang)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Engine)
add_executable(Engine
    src/OpenGL.cpp
    src/Renderer/Vertex.cpp
    src/Math/Vector2.cpp
    src/Math/Vector3.cpp
    src/Math/Vector4.cpp
    src/Math/Matrix2.cpp
    src/Renderer/Shader.cpp
    src/Renderer/Geometry.cpp
    src/FileSystem/FileSystem.cpp
    src/Renderer/Texture.cpp
    src/Renderer/Material.cpp
    Libraries/lib/glad.c

)


find_package(glfw3 REQUIRED)

target_include_directories(Engine PRIVATE
    Libraries/include
)

target_link_libraries(Engine
    glfw
    GL
)
