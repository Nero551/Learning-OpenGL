#include "Input.hpp"
#include "Core/Core.hpp"
#include <OpenGL.hpp>

bool Input::IsKeyDown(Key key) {
  return glfwGetKey(Engine::Instance->window.GetGlfwWindow(), static_cast<int>(key)) == GLFW_PRESS;
}