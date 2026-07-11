#include "World.hpp"

#include <ranges>

#include "Core/ResourceManager.hpp"
#include "Engine.hpp"
#include "Modules/Renderer/Entities/Cube.hpp"
#include "Modules/Renderer/Systems/CameraSystem.hpp"
#include "Utilities/Services/LoggerService.hpp"
#include "World/Scenes/FirstScene.hpp"

void World::AddSystems() {
   AddSystem<CameraSystem>();
}

void World::Start() {
   AddSystems();

   auto &resourceManager = Engine::Ins->ResourceManager;
   auto &scene = CreateScene<FirstScene>("First Scene");
   SetActiveScene(scene);

   Vector4 lightColor{1, 1, 1, 1};
   Vector4 toyColor{1, 0.5, 0.31, 1};

   LoggerService::Info(lightColor * toyColor);

   auto &shader = resourceManager.Load<Shader>("shader", "Assets/Shaders/shader.frag",
      "Assets/Shaders/shader.vert");
   auto &material = resourceManager.Load<Material>("material");
   material.AssignShader(shader);

   Cube &cube = scene.CreateEntity<Cube>();
   cube.GetComponent<MaterialComponent>().Material = &material;

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

void World::BeginFrame(double dt) {
   for (auto &system: Systems | std::views::values) {
      system->BeginFrame(dt);
   }
}

void World::EndFrame(double dt) {
   for (auto &system: Systems | std::views::values) {
      system->EndFrame(dt);
   }
}
