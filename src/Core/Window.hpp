#pragma once
#include <OpenGL.hpp>

struct Window {
  int Width;
  int Height;

  Window(int width, int height, const char *name);
  ~Window();

  bool ShouldClose();
  void SwapBuffers();
  void PollEvents();
  void Close();

  GLFWwindow *GetGlfwWindow();

private:
  GLFWwindow *GlfwWindow;
};
