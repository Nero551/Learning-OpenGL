#include "Input.hpp"
#include "Core/Engine.hpp"
#include <OpenGL.hpp>
#include "magic_enum/magic_enum.hpp"

void Input::OnStart() {
   Window &window = Engine::Ins->Window;
   glfwSetCursorPosCallback(window.GetGlfwWindow(), [](GLFWwindow *, double xPos, double yPos) {
      Engine::Ins->GetModule<Input>().mousePosition = Vector2(static_cast<float>(xPos), static_cast<float>(yPos));
   });

   glfwSetScrollCallback(window.GetGlfwWindow(), [](GLFWwindow *, double xOffset, double yOffset) {
      Engine::Ins->GetModule<Input>().scrollOffset = Vector2(static_cast<float>(xOffset), static_cast<float>(yOffset));
   });
}

void Input::OnBeginFrame(double dt) {
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

void Input::OnEndFrame(double dt) {
   scrollOffset = {0, 0};
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

void Input::SetMouseMode(MouseMode mode) {
   mouseMode = mode;
   glfwSetInputMode(Engine::Ins->Window.GetGlfwWindow(), GLFW_CURSOR, static_cast<int>(mode));
}

Vector2 Input::GetMousePosition() const { return mousePosition; }

Vector2 Input::GetMouseDelta() const { return (GetMousePosition() - previousMousePosition); }

MouseMode Input::GetMouseMode() const { return mouseMode; }

Vector2 Input::GetScrollDelta() const { return scrollOffset; }

bool Input::IsScrolling() const {
   return scrollOffset != Vector2::Zero;
}
