#include "World.hpp"
#include "Engine.hpp"
#include "Modules/Renderer/Entities/Camera.hpp"
#include "Modules/Renderer/Systems/CameraSystem.hpp"
#include "Utilities/Math/Basis.hpp"

#include <ranges>

void World::AddSystems() { AddSystem<CameraSystem>(); }

void World::Start() {
  AddSystems();

  Scene &scene = CreateScene<Scene>("First Scene");
  Camera &camera = scene.CreateEntity<Camera>();
  camera.GetComponent<CameraComponent>().AspectRatio = 800.0f / 600.0f;
  scene.SetActiveCamera(camera);
  SetActiveScene(scene);

  for (auto &system : Systems | std::views::values) {
    system->Start();
  }

  //? Quick tests
  Matrix4 m = Matrix4::Identity;

  m = m.RotateY(Math::DegToRad(90));
  m = m.RotateX(Math::DegToRad(90));

  Vector4 v(0, 0, 1, 1);

  LoggerService::Print(m * v);
}

void World::Update(double dt) {

  for (auto &system : Systems | std::views::values) {
    system->Update(dt);
  }
}

void World::Stop() {

  for (auto &system : Systems | std::views::values) {
    system->Stop();
  }
}