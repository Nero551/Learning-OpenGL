#include "CameraSystem.hpp"
#include "Utilities/Math/MathUtils.hpp"
#include "Core/InnerCore/Engine.hpp"
#include "Modules/Input/Input.hpp"
#include "Modules/Renderer/Components/CameraComponent.hpp"
#include "World/Components/Transform3DComponent.hpp"

namespace E {
void CameraSystem::Update(double dt) {
    {
        auto& input = Engine::Get().GetModule<Input>();
        auto& camera = World::Get().ActiveCamera;
        auto& transform = camera->GetComponent<Transform3DComponent>();
        auto& cameraComponent = camera->GetComponent<CameraComponent>();

        cameraComponent.AspectRatio = Engine::Get().Window.GetAspectRatio();

        if (input.GetMouseMode() == MouseMode::Disabled) {
            cameraComponent.Speed += input.GetScrollDelta().y / 3;
            cameraComponent.Speed = std::clamp(cameraComponent.Speed, 5.0f, 50.0f);

            const float xOffset = Math::Rad(input.GetMouseDelta().x * cameraComponent.Sensitivity);
            const float yOffset = Math::Rad(-input.GetMouseDelta().y * cameraComponent.Sensitivity);

            const float maxPitch = Math::Rad(89.0f);

            transform.Rotation.y += xOffset;
            transform.Rotation.x += yOffset;
            transform.Rotation.x = std::clamp(transform.Rotation.x, -maxPitch, maxPitch);
        }

        const float speed = cameraComponent.Speed * static_cast<float>(dt);

        if (input.IsKeyHeld(Key::W)) {
            transform.Position += speed * transform.GetForward();
        }

        if (input.IsKeyHeld(Key::S)) {
            transform.Position -= speed * transform.GetForward();
        }

        if (input.IsKeyHeld(Key::A)) {
            transform.Position -= speed * transform.GetRight();
        }

        if (input.IsKeyHeld(Key::D)) {
            transform.Position += speed * transform.GetRight();
        }

        if (input.IsKeyHeld(Key::Space)) {
            transform.Position += speed * Vector3(0, 1, 0);
        }

        if (input.IsKeyHeld(Key::LeftShift)) {
            transform.Position -= speed * Vector3(0, 1, 0);
        }
    }
}

Matrix4 CameraSystem::GetViewMatrix() {
    auto& camera = World::Get().ActiveCamera;
    auto& transformComponent = camera->GetComponent<Transform3DComponent>();

    Vector3 pos = transformComponent.Position;
    Vector3 forward = transformComponent.GetForward();
    Vector3 up = transformComponent.GetUp();

    Matrix4 view = Matrix4::LookAt(pos, pos + forward, up);

    return view;
}
}
