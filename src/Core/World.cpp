#include "World.hpp"

#include <ranges>

#include "Core/ResourceManager.hpp"
#include "Engine.hpp"
#include "Modules/Renderer/Entities/Cube.hpp"
#include "Modules/Renderer/Systems/CameraSystem.hpp"
#include "World/Scenes/FirstScene.hpp"

void World::AddSystems() { AddSystem<CameraSystem>(); }

void World::Start() {
   AddSystems();

   auto &resourceManager = Engine::Ins->ResourceManager;
   auto &scene = CreateScene<FirstScene>("First Scene");
   SetActiveScene(scene);

   auto &shader = resourceManager.Load<Shader>("shader", "Assets/Shaders/shader.frag", "Assets/Shaders/shader.vert");
   auto &material = resourceManager.Load<Material>("material");
   material.AssignShader(shader);

   Cube &cube = scene.CreateEntity<Cube>();
   cube.GetComponent<MaterialComponent>().Material = &material;

   Cube &cube2 = scene.CreateEntity<Cube>();
   cube2.GetComponent<MaterialComponent>().Material = &material;

   Cube &cube3 = scene.CreateEntity<Cube>();
   cube3.GetComponent<MaterialComponent>().Material = &material;

   for (auto &system: Systems | std::views::values) {
      system->Start();
   }
}

void World::Update(double dt) {
   for (auto &system: Systems | std::views::values) {
      system->Update(dt);
   }
}

void World::Stop() {
   for (auto &system: Systems | std::views::values) {
      system->Stop();
   }
}
