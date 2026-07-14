#pragma once
#include "OpenGL.hpp"

enum class Topology {
   Points = GL_POINTS,
   Lines = GL_LINES,
   Triangles = GL_TRIANGLES,
   TriangleStrip = GL_TRIANGLE_STRIP,
   LineStrip = GL_LINE_STRIP,
};
