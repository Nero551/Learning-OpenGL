#include "Input.hpp"
#include "Core/Engine.hpp"
#include <OpenGL.hpp>

bool Input::IsKeyDown(Key key) {
  return glfwGetKey(Engine::Instance->window.GetGlfwWindow(), static_cast<int>(key)) == GLFW_PRESS;
}

void Input::SetMouseMode(enum MouseMode mode) {
  glfwSetInputMode(Engine::Instance->window.GetGlfwWindow(), GLFW_CURSOR, static_cast<int>(mode));
}

void Input::Start() {
  glfwSetCursorPosCallback(Engine::Instance->window.GetGlfwWindow(), [](GLFWwindow *, double xPos, double yPos) {
    Engine::Instance->ModuleStore.InputModule.MousePosition =
      Vector2(static_cast<float>(xPos), static_cast<float>(yPos));
  });
}