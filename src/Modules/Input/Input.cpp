#include "Input.hpp"
#include "Core/Engine.hpp"
#include <OpenGL.hpp>
#include "magic_enum/magic_enum.hpp"
#include "Utilities/Services/LoggerService.hpp"

void Input::Start() {
  glfwSetCursorPosCallback(Engine::Ins->Window.GetGlfwWindow(), [](GLFWwindow *, double xPos, double yPos) {
    Engine::Ins->GetModule<Input>().mousePosition = Vector2(static_cast<float>(xPos), static_cast<float>(yPos));
  });
}

void Input::BeginFrame(double dt) {
  if (firstMouse) {
    previousMousePosition = GetMousePosition();
    firstMouse = false;
  }

  GLFWwindow *window = Engine::Ins->Window.GetGlfwWindow();
  for (unsigned int i = 0; i < CurrentKeys.size(); i++) {
    CurrentKeys[i] = glfwGetKey(window, static_cast<int>(i)) == GLFW_PRESS;
  }

  for (unsigned int i = 0; i < CurrentMouseButtons.size(); i++) {
    CurrentMouseButtons[i] = glfwGetMouseButton(window, static_cast<int>(i));
  }
}

void Input::EndFrame(double dt) {
  previousMousePosition = mousePosition;
  PreviousKeys = CurrentKeys;
  PreviousMouseButtons = CurrentMouseButtons;
}

bool Input::IsKeyHeld(Key key) {
  return CurrentKeys[ToIndex(key)];
}

bool Input::IsKeyPressed(Key key) {
  return CurrentKeys[ToIndex(key)] && !PreviousKeys[ToIndex(key)];
}

bool Input::IsKeyReleased(Key key) {
  return !CurrentKeys[ToIndex(key)] && PreviousKeys[ToIndex(key)];
}

bool Input::IsMouseButtonHeld(MouseButton button) {
  return CurrentMouseButtons[ToIndex(button)];
}

bool Input::IsMouseButtonPressed(MouseButton button) {
  return CurrentMouseButtons[ToIndex(button)] && !PreviousMouseButtons[ToIndex(button)];
}

bool Input::IsMouseButtonReleased(MouseButton button) {
  return !CurrentMouseButtons[ToIndex(button)] && PreviousMouseButtons[ToIndex(button)];
}

void Input::SetMouseMode(enum MouseMode mode) {
  mouseMode = mode;
  glfwSetInputMode(Engine::Ins->Window.GetGlfwWindow(), GLFW_CURSOR, static_cast<int>(mode));
}

Vector2 Input::GetMousePosition() { return mousePosition; }

Vector2 Input::GetMouseDelta() {
  return (GetMousePosition() - previousMousePosition);
}

enum MouseMode Input::GetMouseMode() { return mouseMode; }