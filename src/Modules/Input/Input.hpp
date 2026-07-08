#pragma once

#include "Core/Module.hpp"
#include <OpenGL.hpp>

enum class Key {
  A = GLFW_KEY_A,
  B = GLFW_KEY_B,
  C = GLFW_KEY_C,
  W = GLFW_KEY_W,
  Escape = GLFW_KEY_ESCAPE,
  Space = GLFW_KEY_SPACE,
  LeftShift = GLFW_KEY_LEFT_SHIFT,
};

struct Input : Module {
  bool IsKeyDown(Key key);
};