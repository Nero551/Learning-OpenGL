#include "Renderer.hpp"
#include "Core/Engine.hpp"

void Renderer::Start() {}

void Renderer::Update(double dt) {}

void Renderer::Render() {
  auto camera = Engine::Instance->World.ActiveScene->ActiveCamera;

  Matrix4 projection = Engine::Instance->World.ActiveScene->ActiveCamera->cameraComponent.GetProjectionMatrix();
  Matrix4 view = Matrix4::LookAt(camera->transformComponent.Position,
    camera->transformComponent.Position + camera->transformComponent.Forward, camera->transformComponent.GetUp());

  for (Object object : Objects) {
    object.Draw(view, projection);
  }
}

void Renderer::Stop() {}