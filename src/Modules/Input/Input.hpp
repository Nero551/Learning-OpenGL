#pragma once

#include "Enums/Keys.hpp"
#include "Core/InnerCore/Module.hpp"
#include "Math/Vector/Vector2.hpp"
#include "Enums/Mouse.hpp"

namespace E {
struct Input : Module {
    bool IsKeyHeld(Key key);

    bool IsKeyPressed(Key key);

    bool IsKeyReleased(Key key);

    bool IsMouseButtonHeld(MouseButton button);

    bool IsMouseButtonPressed(MouseButton button);

    bool IsMouseButtonReleased(MouseButton button);

    M::Vector2 GetMousePosition() const;

    M::Vector2 GetMouseDelta() const;

    M::Vector2 GetScrollDelta() const;

    bool IsScrolling() const;

    MouseMode GetMouseMode() const;

    void SetMouseMode(MouseMode mode);

private:
    MouseMode mouseMode = MouseMode::Normal;
    M::Vector2 mousePosition = M::Vector2::Zero;
    M::Vector2 previousMousePosition = M::Vector2::Zero;
    bool firstMouse = true;

    M::Vector2 scrollOffset = M::Vector2::Zero;

    static constexpr unsigned int MouseButtonCount = GLFW_MOUSE_BUTTON_LAST + 1;
    static constexpr unsigned int KeyCount = GLFW_KEY_LAST + 1;

    constexpr unsigned int ToIndex(Key key);

    constexpr unsigned int ToIndex(MouseButton button);

    std::array<bool, KeyCount> CurrentKeys{};
    std::array<bool, KeyCount> PreviousKeys{};

    std::array<bool, MouseButtonCount> CurrentMouseButtons{};
    std::array<bool, MouseButtonCount> PreviousMouseButtons{};

protected:
    void OnStart() override;

    void OnBeginFrame(double dt) override;

    void OnEndFrame(double dt) override;
};
}

