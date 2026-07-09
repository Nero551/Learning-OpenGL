#include "World.hpp"

Scene &World::CreateScene() {
  auto &scene = Scenes.emplace_back(std::make_unique<Scene>());
  return *scene;
}

void World::SetActiveScene(Scene &scene) { ActiveScene = &scene; }

void World::Start() {
  Scene &scene = CreateScene();
  SetActiveScene(scene);

  // TODO- camera will be an entity inside the scene
}

void World::Update() {}

void World::Stop() {}