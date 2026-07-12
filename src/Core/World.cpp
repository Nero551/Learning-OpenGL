#include "World.hpp"

#include "Core/ResourceManager.hpp"
#include "Engine.hpp"
#include "Modules/Renderer/Entities/Cube.hpp"
#include "Modules/Renderer/Entities/Light.hpp"
#include "Modules/Renderer/Uniforms/Vector3Uniform.hpp"
#include "Modules/Renderer/Uniforms/Vector4Uniform.hpp"
#include "World/Scenes/FirstScene.hpp"

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

   objectShader.SetUniform(Vector4Uniform("ObjectColor", {0.3, 0.3, 0.3, 1}));
   objectShader.SetUniform(Vector4Uniform("LightColor", {1, 1, 1, 1}));
   objectShader.SetUniform(Vector3Uniform("LightPosition", {1.2, 1, 2}));

   auto &objectMaterial = resourceManager.Load<Material>("material");
   objectMaterial.AssignShader(objectShader);

   Cube &cube = scene.CreateEntity<Cube>();
   cube.GetComponent<MaterialComponent>().Material = &objectMaterial;
   cube.GetComponent<MeshComponent>().Mesh = &mesh;

   auto &lightShader = resourceManager.Load<Shader>("lightShader", "Assets/Shaders/lightShader.frag",
      "Assets/Shaders/lightShader.vert");

   auto &lightMaterial = resourceManager.Load<Material>("lightMaterial");
   lightMaterial.AssignShader(lightShader);

   Light &light = scene.CreateEntity<Light>();
   light.GetComponent<MaterialComponent>().Material = &lightMaterial;
   light.GetComponent<MeshComponent>().Mesh = &mesh;

   light.GetComponent<TransformComponent>().Position = {1.2, 1, 2};
   light.GetComponent<TransformComponent>().Scale = {0.2, 0.2, 0.2};
}

void World::Update(double dt) {}

void World::Stop() {}

void World::BeginFrame(double dt) {}

void World::EndFrame(double dt) {}
