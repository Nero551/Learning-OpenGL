#include "Input.hpp"
#include "Core/Engine.hpp"
#include <OpenGL.hpp>

bool Input::IsKeyDown(Key key) {
    return glfwGetKey(Engine::Ins->Window.GetGlfwWindow(), static_cast<int>(key)) == GLFW_PRESS;
}

void Input::SetMouseMode(enum MouseMode mode) {
    glfwSetInputMode(Engine::Ins->Window.GetGlfwWindow(), GLFW_CURSOR, static_cast<int>(mode));
}

void Input::Start() {
    glfwSetCursorPosCallback(Engine::Ins->Window.GetGlfwWindow(), [](GLFWwindow *, double xPos, double yPos) {
        Engine::Ins->GetModule<Input>().MousePosition = Vector2(static_cast<float>(xPos), static_cast<float>(yPos));
    });
}