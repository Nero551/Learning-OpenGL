#pragma once
#include "Module.hpp"
#include "Window.hpp"
#include "World/World.hpp"
#include <vector>

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
