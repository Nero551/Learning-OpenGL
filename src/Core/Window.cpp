#include "Window.hpp"

#include "Engine.hpp"
#include "Utilities/Services/LoggerService.hpp"

Window::Window(int width, int height, const char *name) {
  Width = width;
  Height = height;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(width, height, name, nullptr, nullptr);
  if (!window) {
    LoggerService::Error("Failed To Create Window");
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    LoggerService::Error("Failed To Initialize GLAD");
  }

  glViewport(0, 0, width, height);
  glfwSetFramebufferSizeCallback(window, [](GLFWwindow *, int width, int height) {
    glViewport(0, 0, width, height);
    Engine::Instance->window.Width = width;
    Engine::Instance->window.Height = height;
  });
  GlfwWindow = window;
  glEnable(GL_DEPTH_TEST);
}

Window::~Window() { glfwDestroyWindow(GlfwWindow); }

GLFWwindow *Window::GetGlfwWindow() { return GlfwWindow; }
bool Window::ShouldClose() { return glfwWindowShouldClose(GlfwWindow); }
void Window::SwapBuffers() { glfwSwapBuffers(GlfwWindow); }
void Window::PollEvents() { glfwPollEvents(); }

void Window::Close() { glfwSetWindowShouldClose(GlfwWindow, true); }