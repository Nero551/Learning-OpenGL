#include "TransformSystem.hpp"

#include "Core/InnerCore/Engine.hpp"
#include "World/Components/Transform3DComponent.hpp"

void TransformSystem::Start() {}

void TransformSystem::FixedUpdate(double fdt) {
    for (auto& entity : Engine::Get().World.ActiveScene->GetRoot().GetDescendants()) {
        if (!entity->HasComponent<Transform3DComponent>()) {
            continue;
        }

        auto& transform = entity->GetComponent<Transform3DComponent>();

        if (entity->HasParent() && transform.InheritTransform == true) {
            auto& parent = entity->GetParent();
            if (parent.HasComponent<Transform3DComponent>()) {
                auto& parentTransform = parent.GetComponent<Transform3DComponent>();

                transform.GlobalPosition = parentTransform.GlobalPosition + transform.LocalPosition;
                transform.GlobalEulerRotation = parentTransform.GlobalEulerRotation + transform.LocalEulerRotation;
                transform.GlobalScale = parentTransform.GlobalScale * transform.LocalScale;
            }
        }
        else {
            transform.GlobalPosition = transform.LocalPosition;
            transform.GlobalEulerRotation = transform.LocalPosition;
            transform.GlobalScale = transform.LocalScale;
        }
    }
}
