#include "Engine.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

Window::Window(int width, int height, std::string name) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
  if (!window) {
    std::cout << "Failed To Create Window";
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed To Initialize GLAD";
  }

  glViewport(0, 0, width, height);
  glfwSetFramebufferSizeCallback(window,
    [](GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); });

  GlfwWindow = window;
}

Window::~Window() {
  glfwDestroyWindow(GlfwWindow);
  glfwTerminate();
}

bool Window::ShouldClose() { return glfwWindowShouldClose(GlfwWindow); }
void Window::SwapBuffers() { glfwSwapBuffers(GlfwWindow); }

void Window::ProcessInput() {
  if (glfwGetKey(GlfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(GlfwWindow, true);
  }
}