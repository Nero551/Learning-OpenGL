#include "Input.h"
#include "Core/Core.h"
#include <GLFW/glfw3.h>

bool Input::IsKeyDown(Key key) {
  return glfwGetKey(Engine::Instance->window.GetGlfwWindow(), static_cast<int>(key)) == GLFW_PRESS;
}