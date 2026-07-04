module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

import LoggerService;

export module Window;

export struct Window {
  Window(int width, int height, std::string name) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    if (!window) {
      LoggerService::Error("Failed To Create Window");
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      LoggerService::Error("Failed To Initialize GLAD");
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window,
      [](GLFWwindow *, int width, int height) { glViewport(0, 0, width, height); });

    GlfwWindow = window;
  }
  ~Window() { glfwDestroyWindow(GlfwWindow); }

  bool ShouldClose() { return glfwWindowShouldClose(GlfwWindow); }
  void SwapBuffers() { glfwSwapBuffers(GlfwWindow); }
  void ProcessInput() {
    if (glfwGetKey(GlfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(GlfwWindow, true);
    }
  }

  GLFWwindow *GetGlfwWindow() { return GlfwWindow; }

private:
  GLFWwindow *GlfwWindow;
};
