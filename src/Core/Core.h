#pragma once
#include <GLFW/glfw3.h>
#include <concepts>
#include <string>
#include <vector>

struct Window {
  Window(int width, int height, std::string name);
  ~Window();

  bool ShouldClose();
  void SwapBuffers();
  void ProcessInput();

private:
  GLFWwindow *GlfwWindow;
};

struct Module {
  virtual void Start() {}
  virtual void Update(double dt) {}
  virtual void Stop() {}
  virtual ~Module() {}
};


struct Engine {
  std::vector<Module> Modules;
  const double DeltaTime = 0.016;
  bool Running;
  double Time;
  Window window;

  Engine();
  void Start();
  void Stop();

  void BeginFrame();
  void EndFrame();
  void Update();
  void Render();
};
