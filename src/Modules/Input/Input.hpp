#pragma once

#include "Enums/Keys.hpp"
#include "Core/InnerCore/Module.hpp"
#include "Utilities/Math/Vector/Vector2.hpp"
#include "Enums/Mouse.hpp"

struct Input : Module
{
   bool IsKeyHeld(Key key);

   bool IsKeyPressed(Key key);

   bool IsKeyReleased(Key key);

   bool IsMouseButtonHeld(MouseButton button);

   bool IsMouseButtonPressed(MouseButton button);

   bool IsMouseButtonReleased(MouseButton button);

   Vector2 GetMousePosition() const;

   Vector2 GetMouseDelta() const;

   Vector2 GetScrollDelta() const;

   bool IsScrolling() const;

   MouseMode GetMouseMode() const;

   void SetMouseMode(enum MouseMode mode);

private:
   MouseMode mouseMode = MouseMode::Normal;
   Vector2 mousePosition = Vector2::Zero;
   Vector2 previousMousePosition = Vector2::Zero;
   bool firstMouse = true;

   Vector2 scrollOffset = Vector2::Zero;

   static constexpr unsigned int MouseButtonCount = GLFW_MOUSE_BUTTON_LAST + 1;
   static constexpr unsigned int KeyCount = GLFW_KEY_LAST + 1;

   constexpr unsigned int ToIndex(Key key)
   {
      return static_cast<unsigned int>(key);
   }

   constexpr unsigned int ToIndex(MouseButton button)
   {
      return static_cast<unsigned int>(button);
   }

   std::array<bool, KeyCount> CurrentKeys{};
   std::array<bool, KeyCount> PreviousKeys{};

   std::array<bool, MouseButtonCount> CurrentMouseButtons{};
   std::array<bool, MouseButtonCount> PreviousMouseButtons{};

protected:
   void OnStart() override;

   void OnBeginFrame(double dt) override;

   void OnEndFrame(double dt) override;
};
