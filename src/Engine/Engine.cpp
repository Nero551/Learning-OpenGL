#include "../Depth/Depth.h"
#include "Engine.h"
#include <iostream>

Entity entity;

void Engine::Start() { entity.Velocity = {0, 5, 0}; }

void Engine::Process(double dt) {
  entity.Position += entity.Velocity * dt;
  std::cout << entity.Position << "\n";
}

void Engine::Stop() {}
