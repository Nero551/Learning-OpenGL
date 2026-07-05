#pragma once
#include <OpenGL.hpp>
#include <concepts>
#include <string>
#include <vector>
#include "World/World.hpp"

struct Window {
  Window(int width, int height, std::string name);
  ~Window();

  bool ShouldClose();
  void SwapBuffers();
  void Close();

  GLFWwindow *GetGlfwWindow();

private:
  GLFWwindow *GlfwWindow;
};

struct Module {
  virtual void Start() {}
  virtual void Update(double dt) {}
  virtual void Stop() {}
  virtual ~Module() {}
};

//TODO- make each cpp file have itts own header to fix cyclic header dependancy

struct Engine {
  static Engine *Instance;

  std::vector<Module> Modules;
  bool Running;
  double Time = 0;
  double DeltaTime = 0;
  Window window;
  World world;

  Engine();
  void Start();
  void Stop();

  void BeginFrame();
  void EndFrame();
  void Update();
  void Render();

private:
  double LastFrame = 0;
};
