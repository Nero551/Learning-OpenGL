#include "Window.hpp"

#include "Engine.hpp"
#include "Utilities/Logger.hpp"

namespace E {
Window::Window(const int width, const int height, const std::string& title) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHintString(GLFW_WAYLAND_APP_ID, "pu_engine");
    glfwWindowHintString(GLFW_X11_CLASS_NAME, "pu_engine");


    GLFWwindow* glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!glfwWindow) {
        Logger::Error("Failed To Create Window");
    }
    glfwMakeContextCurrent(glfwWindow);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        Logger::Error("Failed To Initialize GLAD");
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(glfwWindow, [](GLFWwindow*, const int w, const int h) {
        glViewport(0, 0, w, h);
    });
    GlfwWindow = glfwWindow;
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

Window::~Window() {
    glfwDestroyWindow(GlfwWindow);
}

float Window::GetAspectRatio() const {
    return static_cast<float>(GetWidth()) / static_cast<float>(GetHeight());
}

GLFWwindow* Window::GetGlfwWindow() {
    return GlfwWindow;
}

bool Window::ShouldClose() {
    return glfwWindowShouldClose(GlfwWindow);
}

void Window::SwapBuffers() {
    glfwSwapBuffers(GlfwWindow);
}

void Window::PollEvents() {
    glfwPollEvents();
}

void Window::SetTitle(const std::string& title) {
    glfwSetWindowTitle(GlfwWindow, title.c_str());
}

int Window::GetHeight() const {
    int height = 0;
    int width = 0;
    glfwGetWindowSize(GlfwWindow, &width, &height);
    return height;
}

int Window::GetWidth() const {
    int height = 0;
    int width = 0;
    glfwGetWindowSize(GlfwWindow, &width, &height);
    return width;
}

void Window::Close() {
    glfwSetWindowShouldClose(GlfwWindow, true);
}

void Window::SetIcon(const Image& icon) {
    GLFWimage image;
    image.height = icon.Height;
    image.width = icon.Width;
    image.pixels = icon.Pixels;
    glfwSetWindowIcon(GlfwWindow, 1, &image);
}

void Window::SetHeight(const int height) {
    glfwSetWindowSize(GlfwWindow, GetWidth(), height);
}

void Window::SetWidth(const int width) {
    glfwSetWindowSize(GlfwWindow, width, GetHeight());
}

void Window::SetSize(const int width, const int height) {
    SetWidth(width);
    SetHeight(height);
}
}
