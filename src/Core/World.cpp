#include "World.hpp"

#include "Core/ResourceManager.hpp"
#include "Engine.hpp"
#include "Modules/Input/Input.hpp"
#include "Modules/Renderer/Entities/Cube.hpp"
#include "Modules/Renderer/Entities/Light.hpp"
#include "Modules/Renderer/Uniforms/Vector3Uniform.hpp"
#include "Modules/Renderer/Uniforms/Vector4Uniform.hpp"
#include "Utilities/Math/Color.hpp"
#include "World/Scenes/FirstScene.hpp"

unsigned int lightId;
unsigned int cubeId;

void World::Start() {
   auto &resourceManager = Engine::Ins->ResourceManager;
   auto &scene = CreateScene<FirstScene>("First Scene");
   SetActiveScene(scene);


   auto &mesh = Engine::Ins->ResourceManager.Load<Mesh>("mesh", std::vector<Vertex>{
      // Front (+Z)
      Vertex({-0.5f, -0.5f, 0.5f, 1}, {1, 0, 0, 1}, {0, 0}, {0, 0, 1}),
      Vertex({0.5f, -0.5f, 0.5f, 1}, {1, 0, 1, 1}, {1, 0}, {0, 0, 1}),
      Vertex({0.5f, 0.5f, 0.5f, 1}, {0, 1, 0, 1}, {1, 1}, {0, 0, 1}),
      Vertex({-0.5f, 0.5f, 0.5f, 1}, {1, 1, 1, 1}, {0, 1}, {0, 0, 1}),

      // Back (-Z)
      Vertex({0.5f, -0.5f, -0.5f, 1}, {1, 0, 0, 1}, {0, 0}, {0, 0, -1}),
      Vertex({-0.5f, -0.5f, -0.5f, 1}, {1, 0, 1, 1}, {1, 0}, {0, 0, -1}),
      Vertex({-0.5f, 0.5f, -0.5f, 1}, {0, 1, 0, 1}, {1, 1}, {0, 0, -1}),
      Vertex({0.5f, 0.5f, -0.5f, 1}, {1, 1, 1, 1}, {0, 1}, {0, 0, -1}),

      // Left (-X)
      Vertex({-0.5f, -0.5f, -0.5f, 1}, {1, 0, 0, 1}, {0, 0}, {-1, 0, 0}),
      Vertex({-0.5f, -0.5f, 0.5f, 1}, {1, 0, 1, 1}, {1, 0}, {-1, 0, 0}),
      Vertex({-0.5f, 0.5f, 0.5f, 1}, {0, 1, 0, 1}, {1, 1}, {-1, 0, 0}),
      Vertex({-0.5f, 0.5f, -0.5f, 1}, {1, 1, 1, 1}, {0, 1}, {-1, 0, 0}),

      // Right (+X)
      Vertex({0.5f, -0.5f, 0.5f, 1}, {1, 0, 0, 1}, {0, 0}, {1, 0, 0}),
      Vertex({0.5f, -0.5f, -0.5f, 1}, {1, 0, 1, 1}, {1, 0}, {1, 0, 0}),
      Vertex({0.5f, 0.5f, -0.5f, 1}, {0, 1, 0, 1}, {1, 1}, {1, 0, 0}),
      Vertex({0.5f, 0.5f, 0.5f, 1}, {1, 1, 1, 1}, {0, 1}, {1, 0, 0}),

      // Top (+Y)
      Vertex({-0.5f, 0.5f, 0.5f, 1}, {1, 0, 0, 1}, {0, 0}, {0, 1, 0}),
      Vertex({0.5f, 0.5f, 0.5f, 1}, {1, 0, 1, 1}, {1, 0}, {0, 1, 0}),
      Vertex({0.5f, 0.5f, -0.5f, 1}, {0, 1, 0, 1}, {1, 1}, {0, 1, 0}),
      Vertex({-0.5f, 0.5f, -0.5f, 1}, {1, 1, 1, 1}, {0, 1}, {0, 1, 0}),

      // Bottom (-Y)
      Vertex({-0.5f, -0.5f, -0.5f, 1}, {1, 0, 0, 1}, {0, 0}, {0, -1, 0}),
      Vertex({0.5f, -0.5f, -0.5f, 1}, {1, 0, 1, 1}, {1, 0}, {0, -1, 0}),
      Vertex({0.5f, -0.5f, 0.5f, 1}, {0, 1, 0, 1}, {1, 1}, {0, -1, 0}),
      Vertex({-0.5f, -0.5f, 0.5f, 1}, {1, 1, 1, 1}, {0, 1}, {0, -1, 0}),
   }, std::vector<unsigned int>{
      0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4, 8, 9, 10, 10, 11, 8, 12, 13, 14, 14, 15, 12, 16, 17, 18, 18, 19, 16, 20, 21,
      22, 22, 23, 20
   });

   auto &objectShader = resourceManager.Load<Shader>("shader", "Assets/Shaders/shader.frag",
      "Assets/Shaders/shader.vert");

   objectShader.SetUniform(Vector3Uniform("LightColor", {1, 1, 1}));

   auto &objectMaterial = resourceManager.Load<Material>("material");
   objectMaterial.AssignShader(objectShader);

   Cube &cube = scene.CreateEntity<Cube>();
   cube.GetComponent<MaterialComponent>().Material = &objectMaterial;
   cube.GetComponent<MeshComponent>().Mesh = &mesh;

   cubeId = cube.Id;

   auto &lightShader = resourceManager.Load<Shader>("lightShader", "Assets/Shaders/lightShader.frag",
      "Assets/Shaders/lightShader.vert");

   auto &lightMaterial = resourceManager.Load<Material>("lightMaterial");
   lightMaterial.AssignShader(lightShader);

   Light &light = scene.CreateEntity<Light>();
   light.GetComponent<MaterialComponent>().Material = &lightMaterial;
   light.GetComponent<MeshComponent>().Mesh = &mesh;

   light.GetComponent<TransformComponent>().Position = {1.2, 1, 2};
   light.GetComponent<TransformComponent>().Scale = {0.2, 0.2, 0.2};

   lightId = light.Id;
}

void World::Update(double dt) {
   Light &light = ActiveScene->GetEntity<Light>(lightId);
   auto &transformComponent = light.GetComponent<TransformComponent>();
   auto &input = Engine::Ins->GetModule<Input>();

   if (input.IsKeyHeld(Key::Up)) {
      transformComponent.Position.z += 2 * dt;
   }
   if (input.IsKeyHeld(Key::Down)) {
      transformComponent.Position.z -= 2 * dt;
   }
   if (input.IsKeyHeld(Key::Left)) {
      transformComponent.Position.x -= 2 * dt;
   }
   if (input.IsKeyHeld(Key::Right)) {
      transformComponent.Position.x += 2 * dt;
   }

   if (input.IsKeyHeld(Key::I)) {
      transformComponent.Position.y += 2 * dt;
   }
   if (input.IsKeyHeld(Key::O)) {
      transformComponent.Position.y -= 2 * dt;
   }

   auto &materialComponent = ActiveScene->GetEntity<Cube>(cubeId).GetComponent<MaterialComponent>();

   materialComponent.Material->GetShader().SetUniform(Vector3Uniform("LightPosition", transformComponent.Position));
}

void World::Stop() {}

void World::BeginFrame(double dt) {}

void World::EndFrame(double dt) {}
