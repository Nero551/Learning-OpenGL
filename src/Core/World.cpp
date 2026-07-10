#include "World.hpp"

#include "Engine.hpp"
#include "Modules/Input/Keys.hpp"

Scene &World::CreateScene() {
  std::unique_ptr<Scene> &scene = Scenes.emplace_back(std::make_unique<Scene>());
  return *scene;
}

void World::SetActiveScene(Scene &scene) { ActiveScene = &scene; }

void World::Start() {
  Scene &scene = CreateScene();
  // scene.ActiveCamera = scene.CreateEntity<Entity>();
  scene.SetActiveCamera(scene.camera);
  SetActiveScene(scene);

  // TODO- camera will be an entity inside the scene
}

constexpr float cameraSpeed = 5;
void World::Update(double dt) {

  ActiveScene->ActiveCamera->ComputeFront();

  if (Engine::Instance->ModuleStore.InputModule.IsKeyDown(Key::W)) {
    ActiveScene->ActiveCamera->Position += cameraSpeed * dt * ActiveScene->ActiveCamera->Front;
  }

  if (Engine::Instance->ModuleStore.InputModule.IsKeyDown(Key::S)) {
    ActiveScene->ActiveCamera->Position -= cameraSpeed * dt * ActiveScene->ActiveCamera->Front;
  }

  if (Engine::Instance->ModuleStore.InputModule.IsKeyDown(Key::A)) {
    ActiveScene->ActiveCamera->Position += cameraSpeed * dt * ActiveScene->ActiveCamera->GetRight();
  }

  if (Engine::Instance->ModuleStore.InputModule.IsKeyDown(Key::D)) {
    ActiveScene->ActiveCamera->Position -= cameraSpeed * dt * ActiveScene->ActiveCamera->GetRight();
  }

  if (Engine::Instance->ModuleStore.InputModule.IsKeyDown(Key::Space)) {
    ActiveScene->ActiveCamera->Position += cameraSpeed * dt * Vector3(0, 1, 0);
  }

  if (Engine::Instance->ModuleStore.InputModule.IsKeyDown(Key::LeftShift)) {
    ActiveScene->ActiveCamera->Position -= cameraSpeed * dt * Vector3(0, 1, 0);
  }
}

void World::Stop() {}