#include "World.hpp"

#include <ranges>

#include "Core/ResourceManager.hpp"
#include "Engine.hpp"
#include "Modules/Renderer/Entities/Cube.hpp"
#include "Modules/Renderer/Entities/Light.hpp"
#include "Modules/Renderer/Systems/CameraSystem.hpp"
#include "Modules/Renderer/Uniforms/FloatUniform.hpp"
#include "Modules/Renderer/Uniforms/Vector3Uniform.hpp"
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

   auto &objectShader = resourceManager.Load<Shader>("shader", "Assets/Shaders/shader.frag",
      "Assets/Shaders/shader.vert");
   auto &objectMaterial = resourceManager.Load<Material>("material");
   objectMaterial.AssignShader(objectShader);
   objectShader.SetUniform(Vector4Uniform("ObjectColor", {1, 0.5, 0.31, 1}));
   objectShader.SetUniform(Vector4Uniform("LightColor", {1, 1, 1, 1}));

   //TODO- unable to set custom uniforms. fix that. issue is: u can't set it after the Use(). gotta queue them and upload on Use()
   //TODO- make a uniform struct with value and Upload method. then all uniform types inherit it.
   //TODO- shader just queues them in a vector and Use() runs Upload on all of them

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
