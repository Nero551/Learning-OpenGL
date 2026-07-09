#include "Engine.hpp"
#include <OpenGL.hpp>
#include "../Modules/Renderer/Renderer.hpp"
#include "Modules/Input/Input.hpp"
#include "Modules/Renderer/Resources/Material.hpp"
#include "Modules/Renderer/Resources/Mesh.hpp"
#include "Modules/Renderer/Resources/Shader.hpp"
#include "Modules/Renderer/Resources/Texture.hpp"
#include "Modules/Renderer/Vertex.hpp"
#include "Utilities/Services/LoggerService.hpp"
#include "World/World.hpp"

Engine::Engine() : window(800, 600, "Plus Ultra") { Running = true; }

/*
  ? engine owns Scenes, or world owns scenes, idc , scenes own entities, entities own components. system run on scene.
  ? 5 things, Resources , Entities , Components , Systems, Utilities

  ? Resources - things that don't really exist, shaders, textures , meshes, etc.
  ? Entities - just ids and contain components.
  ? Components - just data, no logic.
  ? Systems - loop over entities in a scene and does logic on components.
  ? Utilities - it's in the name.
*/

Engine *Engine::Instance = nullptr;

void Engine::Start() {
  World.Start();
  ModuleStore.RendererModule.Start();
  ModuleStore.InputModule.Start();

  std::vector Vertices = {
    // front face
    Vertex({-0.5, -0.5, 0.5, 1}, {1, 0, 0, 1}, {0, 0}), // 0
    Vertex({0.5, -0.5, 0.5, 1}, {1, 0, 1, 1}, {1, 0}),  // 1
    Vertex({0.5, 0.5, 0.5, 1}, {0, 1, 0, 1}, {1, 1}),   // 2
    Vertex({-0.5, 0.5, 0.5, 1}, {1, 1, 1, 1}, {0, 1}),  // 3

    // back face
    Vertex({-0.5, -0.5, -0.5, 1}, {1, 0, 0, 1}, {1, 0}), // 4
    Vertex({0.5, -0.5, -0.5, 1}, {0, 0, 1, 1}, {0, 0}),  // 5
    Vertex({0.5, 0.5, -0.5, 1}, {0, 1, 0, 1}, {0, 1}),   // 6
    Vertex({-0.5, 0.5, -0.5, 1}, {1, 1, 1, 1}, {1, 1})   // 7
  };
  std::vector<unsigned int> Indices = {// front
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
    4, 5, 1, 1, 0, 4};

  auto texture = Texture("rubyTexture", 0, "Assets/Images/ruby.png");
  auto shader = Shader("Assets/Shaders/shader.frag", "Assets/Shaders/shader.vert");

  auto material = Material(shader);

  material.AssignTexture(texture);
  auto mesh = Mesh(Vertices, Indices);
  auto object = Object(mesh, material);

  ModuleStore.RendererModule.Objects.push_back(object);
  ModuleStore.InputModule.SetMouseMode(MouseMode::Disabled);

  auto entity = World.ActiveScene->CreateEntity<Entity>();
  LoggerService::Info(entity.Id);
}

// TODO- first job, make camera an entity and system style

constexpr float cameraSpeed = 5;

void Engine::Update() {
  World.Update();
  Time = glfwGetTime();

  World.ActiveScene->ActiveCamera->ComputeFront();
  if (ModuleStore.InputModule.IsKeyDown(Key::Escape)) {
    Running = false;
    window.Close();
  }
  if (ModuleStore.InputModule.IsKeyDown(Key::W)) {
    World.ActiveScene->ActiveCamera->Position += cameraSpeed * DeltaTime * World.ActiveScene->ActiveCamera->Front;
  }

  if (ModuleStore.InputModule.IsKeyDown(Key::S)) {
    World.ActiveScene->ActiveCamera->Position -= cameraSpeed * DeltaTime * World.ActiveScene->ActiveCamera->Front;
  }
  if (ModuleStore.InputModule.IsKeyDown(Key::A)) {
    World.ActiveScene->ActiveCamera->Position += cameraSpeed * DeltaTime * World.ActiveScene->ActiveCamera->GetRight();
  }
  if (ModuleStore.InputModule.IsKeyDown(Key::D)) {
    World.ActiveScene->ActiveCamera->Position -= cameraSpeed * DeltaTime * World.ActiveScene->ActiveCamera->GetRight();
  }
  if (ModuleStore.InputModule.IsKeyDown(Key::Space)) {
    World.ActiveScene->ActiveCamera->Position += cameraSpeed * DeltaTime * Vector3(0, 1, 0);
  }
  if (ModuleStore.InputModule.IsKeyDown(Key::LeftShift)) {
    World.ActiveScene->ActiveCamera->Position -= cameraSpeed * DeltaTime * Vector3(0, 1, 0);
  }
}

void Engine::Stop() {
  World.Stop();
  glfwTerminate();
}

void Engine::Render() { ModuleStore.RendererModule.Render(); }

void Engine::BeginFrame() {
  window.PollEvents();
  glClearColor(0.1, 0.15, 0.2, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Engine::EndFrame() {
  const float currentFrame = Time;
  DeltaTime = currentFrame - LastFrame;
  LastFrame = currentFrame;

  window.SwapBuffers();
}