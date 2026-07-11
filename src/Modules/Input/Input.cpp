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

  PreviousKeys = CurrentKeys;
  GLFWwindow *window = Engine::Ins->Window.GetGlfwWindow();

  for (unsigned int i = 0; i < CurrentKeys.size(); i++) {
    CurrentKeys[i] = glfwGetKey(window, static_cast<int>(i)) == GLFW_PRESS;
  }
}

void Input::EndFrame(double dt) {
  previousMousePosition = mousePosition;

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

void Input::SetMouseMode(enum MouseMode mode) {
  mouseMode = mode;
  glfwSetInputMode(Engine::Ins->Window.GetGlfwWindow(), GLFW_CURSOR, static_cast<int>(mode));
}

Vector2 Input::GetMousePosition() { return mousePosition; }

Vector2 Input::GetMouseDelta() {
  return (GetMousePosition() - previousMousePosition);
}

enum MouseMode Input::GetMouseMode() { return mouseMode; }