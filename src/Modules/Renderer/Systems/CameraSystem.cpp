#include "CameraSystem.hpp"
#include "Utilities/Math/MathUtils.hpp"
#include "Core/Engine.hpp"
#include "Modules/Input/Input.hpp"

void CameraSystem::Update(double dt) {
  {
    auto &inputModule = Engine::Ins->GetModule<Input>();
    auto &camera = *Engine::Ins->World.ActiveScene->ActiveCamera;
    auto &transform = camera.GetComponent<TransformComponent>();
    const auto &cameraComponent = camera.GetComponent<CameraComponent>();

    if (firstMouse) {
      lastX = inputModule.MousePosition.x;
      lastY = inputModule.MousePosition.y;
      firstMouse = false;
    }

    float xOffset = inputModule.MousePosition.x - lastX;
    float yOffset = lastY - inputModule.MousePosition.y;

    xOffset = Math::DegToRad(xOffset);
    yOffset = Math::DegToRad(yOffset);
    xOffset *= cameraComponent.Sensitivity;
    yOffset *= cameraComponent.Sensitivity;

    lastX = inputModule.MousePosition.x;
    lastY = inputModule.MousePosition.y;

    const float maxPitch = Math::DegToRad(89.0f);

    transform.EulerRotation.y += xOffset;
    transform.EulerRotation.x += yOffset;
    transform.EulerRotation.x = std::clamp(transform.EulerRotation.x, -maxPitch, maxPitch);

    if (inputModule.IsKeyDown(Key::W)) {
      transform.Position += cameraComponent.Speed * dt * transform.GetForward();
    }

    if (inputModule.IsKeyDown(Key::S)) {
      transform.Position -= cameraComponent.Speed * dt * transform.GetForward();
    }

    if (inputModule.IsKeyDown(Key::A)) {
      transform.Position -= cameraComponent.Speed * dt * transform.GetRight();
    }

    if (inputModule.IsKeyDown(Key::D)) {
      transform.Position += cameraComponent.Speed * dt * transform.GetRight();
    }

    if (inputModule.IsKeyDown(Key::Space)) {
      transform.Position += cameraComponent.Speed * dt * Vector3(0, 1, 0);
    }

    if (inputModule.IsKeyDown(Key::LeftShift)) {
      transform.Position -= cameraComponent.Speed * dt * Vector3(0, 1, 0);
    }
  }
}

Matrix4 CameraSystem::GetViewMatrix() {
  auto camera = Engine::Ins->World.ActiveScene->ActiveCamera;
  auto &transformComponent = camera->GetComponent<TransformComponent>();

  Vector3 pos = transformComponent.Position;
  Vector3 forward = transformComponent.GetForward();
  Vector3 up = transformComponent.GetUp();

  Matrix4 view = Matrix4::LookAt(pos, pos + forward, up);

  return view;
}