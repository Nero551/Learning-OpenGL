#include "World.hpp"

#include <ranges>

#include "Core/ResourceManager.hpp"
#include "Engine.hpp"
#include "Modules/Renderer/Entities/Cube.hpp"
#include "Modules/Renderer/Entities/Light.hpp"
#include "Modules/Renderer/Systems/CameraSystem.hpp"
#include "Modules/Renderer/Uniforms/Vector4Uniform.hpp"
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


   auto &ruby = resourceManager.Load<Texture>("ruby", 0, "Assets/Images/ruby.png");
   auto &skull = resourceManager.Load<Texture>("skull", 1, "Assets/Images/skull.png");

   auto &objectShader = resourceManager.Load<Shader>("shader", "Assets/Shaders/shader.frag",
      "Assets/Shaders/shader.vert");

   objectShader.SetUniform(Vector4Uniform("ObjectColor", {1, 0.5, 0.31, 1}));
   objectShader.SetUniform(Vector4Uniform("LightColor", {1, 1, 1, 1}));

   auto &objectMaterial = resourceManager.Load<Material>("material");
   objectMaterial.AssignShader(objectShader);
   objectMaterial.AssignTexture(ruby);
   objectMaterial.AssignTexture(skull);

   Cube &cube = scene.CreateEntity<Cube>();
   cube.GetComponent<MaterialComponent>().Material = &objectMaterial;

   auto &lightShader = resourceManager.Load<Shader>("lightShader",
      "Assets/Shaders/lightShader.frag", "Assets/Shaders/shader.vert");

   Material &lightMaterial = resourceManager.Load<Material>("lightMaterial");
   lightMaterial.AssignShader(lightShader);

   Light &light = scene.CreateEntity<Light>();
   light.GetComponent<MaterialComponent>().Material = &lightMaterial;

   light.GetComponent<TransformComponent>().Position = {2, 2, 2};

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
