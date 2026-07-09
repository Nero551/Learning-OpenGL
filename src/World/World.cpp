#include "World.hpp"

Scene &World::CreateScene() {
  std::unique_ptr<Scene> &scene = Scenes.emplace_back(std::make_unique<Scene>());
  return *scene;
}

void World::SetActiveScene(Scene &scene) { ActiveScene = &scene; }

void World::Start() {
  Scene &scene = CreateScene();
  scene.ActiveCamera = &scene.camera;
  SetActiveScene(scene);

  // TODO- camera will be an entity inside the scene
}

void World::Update() {}

void World::Stop() {}