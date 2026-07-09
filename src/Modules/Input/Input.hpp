#pragma once

#include "Core/Module.hpp"
#include <OpenGL.hpp>

enum class Key {
  A = GLFW_KEY_A,
  B = GLFW_KEY_B,
  C = GLFW_KEY_C,
  W = GLFW_KEY_W,
  S = GLFW_KEY_S,
  D = GLFW_KEY_D,
  E = GLFW_KEY_E,
  Q = GLFW_KEY_Q,
  R = GLFW_KEY_R,
  T = GLFW_KEY_T,
  Y = GLFW_KEY_Y,
  U = GLFW_KEY_U,
  I = GLFW_KEY_I,
  O = GLFW_KEY_O,
  P = GLFW_KEY_P,
  Escape = GLFW_KEY_ESCAPE,
  Space = GLFW_KEY_SPACE,
  LeftShift = GLFW_KEY_LEFT_SHIFT,
};

struct Input : Module {
  bool IsKeyDown(Key key);
};