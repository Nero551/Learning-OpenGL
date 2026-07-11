#pragma once
#include <OpenGL.hpp>
#include <string>

struct Window {
  float Width;
  float Height;

  Window(int width, int height, const std::string &name);

  ~Window();

  bool ShouldClose();

  void SwapBuffers();

  void PollEvents();

  void Close();

  GLFWwindow *GetGlfwWindow();

private:
  GLFWwindow *GlfwWindow;
};
