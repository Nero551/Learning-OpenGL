#pragma once
#include "../OpenGL.h"
#include <string>
class Engine {
public:
  bool Running;

public:
  double Time;

public:
  void Start();

public:
  void Process(double delta);

public:
  void Stop();
};

class Window {
public:
  Window(int width, int height, std::string name);
  ~Window();

  bool ShouldClose();

  void SwapBuffers();

  void ProcessInput();

private:
  GLFWwindow *GlfwWindow;
};