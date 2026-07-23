#pragma once
#include <OpenGL.hpp>

struct Window {
    float Width;
    float Height;

    Window(float width, float height, const std::string& name);

    ~Window();

    bool ShouldClose();

    void SwapBuffers();

    void PollEvents();

    void SetTitle(const std::string& title);

    void Close();

    GLFWwindow* GetGlfwWindow();

    Window(const Window&) = delete;

    Window& operator=(const Window&) = delete;

private:
    GLFWwindow* GlfwWindow;
};
