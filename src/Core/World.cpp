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

   auto &mesh = resourceManager.Load<Mesh>("mesh",
                                           std::vector<Vertex>{
                                              // front face
                                              Vertex({-0.5, -0.5, 0.5, 1}, {1, 0, 0, 1}, {0, 0}), // 0
                                              Vertex({0.5, -0.5, 0.5, 1}, {1, 0, 1, 1}, {1, 0}), // 1
                                              Vertex({0.5, 0.5, 0.5, 1}, {0, 1, 0, 1}, {1, 1}), // 2
                                              Vertex({-0.5, 0.5, 0.5, 1}, {1, 1, 1, 1}, {0, 1}), // 3

                                              // back face
                                              Vertex({-0.5, -0.5, -0.5, 1}, {1, 0, 0, 1}, {1, 0}), // 4
                                              Vertex({0.5, -0.5, -0.5, 1}, {0, 0, 1, 1}, {0, 0}), // 5
                                              Vertex({0.5, 0.5, -0.5, 1}, {0, 1, 0, 1}, {0, 1}), // 6
                                              Vertex({-0.5, 0.5, -0.5, 1}, {1, 1, 1, 1}, {1, 1}) // 7
                                           },
                                           std::vector<unsigned int>{
                                              0, 1, 2, 2, 3, 0,

                                              // back
                                              5, 4, 7, 7, 6, 5,

                                              // left
                                              4, 0, 3, 3, 7, 4,

                                              // right
                                              1, 5, 6, 6, 2, 1,

                                              // top
                                              3, 2, 6, 6, 7, 3,

                                              // bottom
                                              4, 5, 1, 1, 0, 4
                                           });

   Cube &cube = scene.CreateEntity<Cube>();
   cube.GetComponent<MeshComponent>().Mesh = &mesh;
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
