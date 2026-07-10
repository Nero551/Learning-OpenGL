#include "Renderer.hpp"
#include "Core/Engine.hpp"

void Renderer::Start() {}

void Renderer::Update(double dt) {}

void Renderer::Render() {
  auto camera = Engine::Instance->World.ActiveScene->ActiveCamera;

  Matrix4 projection = camera->GetComponent<CameraComponent>().GetProjectionMatrix();

  Vector3 pos = camera->GetComponent<TransformComponent>().Position;
  Vector3 forward = camera->GetComponent<TransformComponent>().Forward;
  Vector3 up = camera->GetComponent<TransformComponent>().GetUp();

  Matrix4 view = Matrix4::LookAt(pos, forward, up);

  for (Object object : Objects) {
    object.Draw(view, projection);
  }
}

void Renderer::Stop() {}