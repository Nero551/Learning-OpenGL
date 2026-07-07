#include "Input.hpp"
#include "Core/Engine.hpp"
#include <OpenGL.hpp>

bool Input::IsKeyDown(Key key) {
  return glfwGetKey(Engine::Instance->window.GetGlfwWindow(), static_cast<int>(key)) == GLFW_PRESS;
}