#pragma once
#include "Core/Scene.hpp"
#include <memory>
#include <vector>

struct World {
  Scene *ActiveScene = nullptr;
  std::vector<std::unique_ptr<Scene>> Scenes;

  Scene &CreateScene(const std::string &name);
  void SetActiveScene(Scene &scene);

  void Start();
  void Update(double dt);
  void Stop();
};
