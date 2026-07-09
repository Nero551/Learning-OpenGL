#pragma once
#include "ModuleStore.hpp"
#include "Window.hpp"
#include "Modules/Renderer/Camera.hpp"
#include "World/World.hpp"

struct Engine {
  static Engine *Instance;

  bool Running;
  double Time = 0;
  double DeltaTime = 0;

  Window window;
  ModuleStore ModuleStore;
  World world;
  Camera Camera;

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
