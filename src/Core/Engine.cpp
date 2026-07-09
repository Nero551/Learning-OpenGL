#include "Engine.hpp"
#include <OpenGL.hpp>
#include "Modules/Renderer/Renderer.hpp"
#include "Modules/Input/Input.hpp"
#include "Modules/Renderer/Material.hpp"
#include "Modules/Renderer/Mesh.hpp"
#include "Modules/Renderer/Shader.hpp"
#include "Modules/Renderer/Texture.hpp"
#include "Modules/Renderer/Vertex.hpp"
#include "Utilities/Math/MathUtils.hpp"
#include "Utilities/Services/LoggerService.hpp"
#include "World/World.hpp"

#include <cmath>

Engine::Engine() : window(800, 600, "Plus Ultra") { Running = true; }

Engine *Engine::Instance = nullptr;

void Engine::Start() {
  ModuleStore.RendererModule.Start();
  ModuleStore.InputModule.Start();

  std::vector<Vertex> Vertices = {
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

  auto texture = Texture(0, "Assets/Images/ruby.png");
  auto shader = Shader("Assets/Shaders/shader.frag", "Assets/Shaders/shader.vert");
  auto material = Material(shader, texture);
  auto mesh = Mesh(Vertices, Indices);
  auto object = Object(mesh, material);

  // object.ModelMatrix = object.ModelMatrix.RotateX(Math::DegToRad(45));
  object.ModelMatrix = object.ModelMatrix.RotateY(Math::DegToRad(45));

  ModuleStore.RendererModule.Objects.push_back(object);
  ModuleStore.InputModule.SetMouseMode(MouseMode::Disabled);
}

constexpr float cameraSpeed = 5;

void Engine::Update() {
  Time = glfwGetTime();

  Camera.ComputeFront();
  if (ModuleStore.InputModule.IsKeyDown(Key::Escape)) {
    Running = false;
    window.Close();
  }
  if (ModuleStore.InputModule.IsKeyDown(Key::W)) {
    Camera.Position += cameraSpeed * DeltaTime * Camera.Front;
  }

  if (ModuleStore.InputModule.IsKeyDown(Key::S)) {
    Camera.Position -= cameraSpeed * DeltaTime * Camera.Front;
  }
  if (ModuleStore.InputModule.IsKeyDown(Key::A)) {
    Camera.Position += cameraSpeed * DeltaTime * Camera.GetRight();
  }
  if (ModuleStore.InputModule.IsKeyDown(Key::D)) {
    Camera.Position -= cameraSpeed * DeltaTime * Camera.GetRight();
  }
  if (ModuleStore.InputModule.IsKeyDown(Key::Space)) {
    Camera.Position += cameraSpeed * DeltaTime * Vector3(0, 1, 0);
  }
  if (ModuleStore.InputModule.IsKeyDown(Key::LeftShift)) {
    Camera.Position -= cameraSpeed * DeltaTime * Vector3(0, 1, 0);
  }
}

void Engine::Stop() { glfwTerminate(); }

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