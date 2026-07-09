#pragma once

#include "Keys.hpp"
#include "Core/Module.hpp"
#include "Utilities/Math/Vector/Vector2.hpp"

enum class MouseMode {
  Normal = GLFW_CURSOR_NORMAL,
  Hidden = GLFW_CURSOR_HIDDEN,
  Disabled = GLFW_CURSOR_DISABLED,
  Captured = GLFW_CURSOR_CAPTURED
};

struct Input : Module {
  MouseMode MouseMode = MouseMode::Normal;
  Vector2 MousePosition = Vector2::Zero;
  bool IsKeyDown(Key key);
  void SetMouseMode(enum MouseMode mode);

  void Start() override;
};