#pragma once
#include "../OpenGL.h"
#include <string>
struct Engine {
  bool Running;
  double Time;
  void Start();
  void Process(double delta);
  void Stop();
};

struct Window {
  Window(int width, int height, std::string name);
  ~Window();

  bool ShouldClose();

  void SwapBuffers();

  void ProcessInput();

private:
  GLFWwindow *GlfwWindow;
};