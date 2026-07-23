#include "Window.hpp"

#include "Engine.hpp"
#include "Utilities/Logger.hpp"

Window::Window(float width, float height, const std::string& name) {
    Width = width;
    Height = height;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHintString(GLFW_WAYLAND_APP_ID, "pu_engine");
    glfwWindowHintString(GLFW_X11_CLASS_NAME, "pu_engine");


    GLFWwindow* window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    if (!window) {
        Logger::Error("Failed To Create Window");
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        Logger::Error("Failed To Initialize GLAD");
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int width, int height) {
        glViewport(0, 0, width, height);
        Engine::Get().Window.Width = width;
        Engine::Get().Window.Height = height;
    });
    GlfwWindow = window;
    glEnable(GL_DEPTH_TEST);
}

Window::~Window() {
    glfwDestroyWindow(GlfwWindow);
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

void Window::Close() {
    glfwSetWindowShouldClose(GlfwWindow, true);
}
