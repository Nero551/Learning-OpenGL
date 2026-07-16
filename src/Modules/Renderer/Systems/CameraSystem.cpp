#include "CameraSystem.hpp"
#include "Utilities/Math/MathUtils.hpp"
#include "Core/InnerCore/Engine.hpp"
#include "Modules/Input/Input.hpp"
#include "Modules/Renderer/Components/CameraComponent.hpp"
#include "Modules/Renderer/Components/Transform3DComponent.hpp"

void CameraSystem::Update(double dt) {
    {
        auto& inputModule = Engine::Ins->GetModule<Input>();
        auto& camera = Engine::Ins->World.ActiveScene->GetActiveCamera();
        auto& transform = camera.GetComponent<Transform3DComponent>();
        auto& cameraComponent = camera.GetComponent<CameraComponent>();

        if (inputModule.GetMouseMode() == MouseMode::Disabled) {
            cameraComponent.Speed += inputModule.GetScrollDelta().y / 3;
            cameraComponent.Speed = std::clamp(cameraComponent.Speed, 5.0f, 50.0f);

            float xOffset = inputModule.GetMouseDelta().x;
            float yOffset = -inputModule.GetMouseDelta().y;

            xOffset = Math::Radians(xOffset);
            yOffset = Math::Radians(yOffset);
            xOffset *= cameraComponent.Sensitivity;
            yOffset *= cameraComponent.Sensitivity;

            const float maxPitch = Math::Radians(89.0f);

            transform.EulerRotation.y += xOffset;
            transform.EulerRotation.x += yOffset;
            transform.EulerRotation.x = std::clamp(transform.EulerRotation.x, -maxPitch, maxPitch);
        }

        if (inputModule.IsKeyHeld(Key::W)) {
            transform.Position += cameraComponent.Speed * dt * transform.GetForward();
        }

        if (inputModule.IsKeyHeld(Key::S)) {
            transform.Position -= cameraComponent.Speed * dt * transform.GetForward();
        }

        if (inputModule.IsKeyHeld(Key::A)) {
            transform.Position -= cameraComponent.Speed * dt * transform.GetRight();
        }

        if (inputModule.IsKeyHeld(Key::D)) {
            transform.Position += cameraComponent.Speed * dt * transform.GetRight();
        }

        if (inputModule.IsKeyHeld(Key::Space)) {
            transform.Position += cameraComponent.Speed * dt * Vector3(0, 1, 0);
        }

        if (inputModule.IsKeyHeld(Key::LeftShift)) {
            transform.Position -= cameraComponent.Speed * dt * Vector3(0, 1, 0);
        }
    }
}

Matrix4 CameraSystem::GetViewMatrix() {
    auto& camera = Engine::Ins->World.ActiveScene->GetActiveCamera();
    auto& transformComponent = camera.GetComponent<Transform3DComponent>();

    Vector3 pos = transformComponent.Position;
    Vector3 forward = transformComponent.GetForward();
    Vector3 up = transformComponent.GetUp();

    Matrix4 view = Matrix4::LookAt(pos, pos + forward, up);

    return view;
}
