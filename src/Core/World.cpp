#include "World.hpp"
#include "Engine.hpp"
#include "Modules/Renderer/Entities/Camera.hpp"
#include "Modules/Renderer/Entities/Cube.hpp"
#include "Modules/Renderer/Systems/CameraSystem.hpp"
#include "Core/ResourceManager.hpp"
#include "Modules/Renderer/Resources/Texture.hpp"

#include <ranges>

void World::AddSystems() { AddSystem<CameraSystem>(); }

void World::Start() {
  AddSystems();

  Scene &scene = CreateScene<Scene>("First Scene");
  Camera &camera = scene.CreateEntity<Camera>();
  camera.GetComponent<CameraComponent>().AspectRatio = Engine::Ins->Window.Width / Engine::Ins->Window.Height;
  scene.SetActiveCamera(camera);
  SetActiveScene(scene);

  auto &resourceManager = Engine::Ins->ResourceManager;

  auto &texture = resourceManager.Load<Texture>("rubyTexture", 0, "Assets/Images/ruby.png");
  auto &shader = resourceManager.Load<Shader>("shader", "Assets/Shaders/shader.frag", "Assets/Shaders/shader.vert");
  auto &material = resourceManager.Load<Material>("material");
  material.AssignShader(shader);
  material.AssignTexture(texture);

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
                                          std::vector<unsigned int>{0, 1, 2, 2, 3, 0,

                                                                    // back
                                                                    5, 4, 7, 7, 6, 5,

                                                                    // left
                                                                    4, 0, 3, 3, 7, 4,

                                                                    // right
                                                                    1, 5, 6, 6, 2, 1,

                                                                    // top
                                                                    3, 2, 6, 6, 7, 3,

                                                                    // bottom
                                                                    4, 5, 1, 1, 0, 4});

  Cube &cube = scene.CreateEntity<Cube>();
  cube.GetComponent<MeshComponent>().Mesh = &mesh;
  cube.GetComponent<MaterialComponent>().Material = &material;

  Cube &cube2 = scene.CreateEntity<Cube>();
  cube2.GetComponent<MeshComponent>().Mesh = &mesh;
  cube2.GetComponent<MaterialComponent>().Material = &material;
  cube2.GetComponent<TransformComponent>().Position = {2, 0, 0};

  Cube &cube3 = scene.CreateEntity<Cube>();
  cube3.GetComponent<MeshComponent>().Mesh = &mesh;
  cube3.GetComponent<MaterialComponent>().Material = &material;
  cube3.GetComponent<TransformComponent>().Position = {2, 0, 2};

  Cube &cube4 = scene.CreateEntity<Cube>();
  cube4.GetComponent<MeshComponent>().Mesh = &mesh;
  cube4.GetComponent<MaterialComponent>().Material = &material;
  cube4.GetComponent<TransformComponent>().Scale = {1, 2.5, 0.7};
  cube4.GetComponent<TransformComponent>().EulerRotation = {Math::DegToRad(45), Math::DegToRad(45), Math::DegToRad(45)};
  cube4.GetComponent<TransformComponent>().Position = {0, 0, 2};

  for (auto &system : Systems | std::views::values) {
    system->Start();
  }
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