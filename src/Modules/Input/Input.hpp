#pragma once

#include "Keys.hpp"
#include "Core/Module.hpp"
#include "Utilities/Math/Vector/Vector2.hpp"
#include "Mouse.hpp"

struct Input : Module {

  bool IsKeyHeld(Key key);

  bool IsKeyPressed(Key key);

  bool IsKeyReleased(Key key);

  bool IsMouseButtonHeld(MouseButton button);

  bool IsMouseButtonPressed(MouseButton button);

  bool IsMouseButtonReleased(MouseButton button);

  Vector2 &GetMousePosition();

  Vector2 &GetMouseDelta();

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