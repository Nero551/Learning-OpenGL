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

void World::Start() {
   auto &resourceManager = Engine::Ins->ResourceManager;
   auto &scene = CreateScene<FirstScene>("First Scene");
   SetActiveScene(scene);

   auto &objectShader = resourceManager.Load<Shader>("shader", "Assets/Shaders/shader.frag",
      "Assets/Shaders/shader.vert");

   objectShader.SetUniform(Vector4Uniform("ObjectColor", {1, 0.5, 0.31, 1}));
   objectShader.SetUniform(Vector4Uniform("LightColor", {1, 1, 1, 1}));

   auto &objectMaterial = resourceManager.Load<Material>("material");
   objectMaterial.AssignShader(objectShader);

   Cube &cube = scene.CreateEntity<Cube>();
   cube.GetComponent<MaterialComponent>().Material = &objectMaterial;

   auto &lightShader = resourceManager.Load<Shader>("lightShader", "Assets/Shaders/lightShader.frag",
      "Assets/Shaders/shader.vert");

   auto &lightMaterial = resourceManager.Load<Material>("lightMaterial");
   lightMaterial.AssignShader(lightShader);

   Light &light = scene.CreateEntity<Light>();
   light.GetComponent<MaterialComponent>().Material = &lightMaterial;

   light.GetComponent<TransformComponent>().Position = {2, 2, 2};
}

void World::Update(double dt) {}

void World::Stop() {}

void World::BeginFrame(double dt) {}

void World::EndFrame(double dt) {}
