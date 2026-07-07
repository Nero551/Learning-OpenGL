#pragma once
#include <OpenGL.hpp>

struct Window {
  Window(int width, int height, const char* name);
  ~Window();

  bool ShouldClose();
  void SwapBuffers();
  void Close();

  GLFWwindow *GetGlfwWindow();

private:
  GLFWwindow *GlfwWindow;
};
