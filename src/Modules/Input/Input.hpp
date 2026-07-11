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

  bool IsKeyHeld(Key key);

  bool IsKeyPressed(Key key);

  bool IsKeyReleased(Key key);

  Vector2 &GetMousePosition();

  enum MouseMode GetMouseMode();

  void SetMouseMode(enum MouseMode mode);

  void Start() override;

  void BeginFrame(double dt) override;

private:
  MouseMode MouseMode = MouseMode::Normal;
  Vector2 MousePosition = Vector2::Zero;

  static constexpr unsigned int KeyCount = GLFW_KEY_LAST + 1;

  constexpr unsigned int ToIndex(Key key) {
    return static_cast<unsigned int>(key);
  }

  std::array<bool, KeyCount> CurrentKeys{};
  std::array<bool, KeyCount> PreviousKeys{};
};