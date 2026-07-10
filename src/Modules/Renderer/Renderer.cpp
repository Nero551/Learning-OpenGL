#include "Renderer.hpp"
#include "Core/Engine.hpp"

void Renderer::Start() {}

void Renderer::Update(double dt) {}

Matrix4 CreateViewMatrix() {
  auto camera = Engine::Instance->World.ActiveScene->ActiveCamera;

  Vector3 pos = camera->GetComponent<TransformComponent>().Position;
  Vector3 forward = camera->GetComponent<TransformComponent>().GetForward();
  Vector3 up = camera->GetComponent<TransformComponent>().GetUp();

  Matrix4 view = Matrix4::LookAt(pos, pos + forward, up);

  return view;
}

void Renderer::Render() {
  auto camera = Engine::Instance->World.ActiveScene->ActiveCamera;

  Matrix4 projection = camera->GetComponent<CameraComponent>().GetProjectionMatrix();
  Matrix4 view = CreateViewMatrix();

  for (Object object : Objects) {
    object.Draw(view, projection);
  }
}

void Renderer::Stop() {}