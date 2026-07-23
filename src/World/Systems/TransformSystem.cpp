#include "TransformSystem.hpp"

#include "Core/InnerCore/Engine.hpp"
#include "World/Components/Transform3DComponent.hpp"

void TransformSystem::Start() {}

void TransformSystem::Update(double dt) {
    for (auto& entity : Engine::Get().World.ActiveScene->GetRoot().GetDescendants()) {
        if (!entity->HasComponent<Transform3DComponent>()) {
            continue;
        }

        auto& transform = entity->GetComponent<Transform3DComponent>();

        if (entity->HasParent() && transform.InheritTransform) {
            auto& parent = entity->GetParent();
            if (parent.HasComponent<Transform3DComponent>()) {
                auto& parentTransform = parent.GetComponent<Transform3DComponent>();

                // Position
                if (transform.LocalPosition.IsDirty() || parentTransform.GlobalPosition.IsDirty()) {
                    transform.GlobalPosition = parentTransform.GlobalPosition.Get() + transform.LocalPosition.Get();
                }

                if (transform.GlobalPosition.IsDirty() || parentTransform.GlobalPosition.IsDirty()) {
                    transform.LocalPosition = transform.GlobalPosition.Get() - parentTransform.GlobalPosition.Get();
                }

                // Rotation
                if (transform.LocalEulerRotation.IsDirty() || parentTransform.GlobalEulerRotation.IsDirty()) {
                    transform.GlobalEulerRotation =
                        parentTransform.GlobalEulerRotation.Get() + transform.LocalEulerRotation.Get();
                }

                if (transform.GlobalEulerRotation.IsDirty() || parentTransform.GlobalEulerRotation.IsDirty()) {
                    transform.LocalEulerRotation =
                        transform.GlobalEulerRotation.Get() - parentTransform.GlobalEulerRotation.Get();
                }

                // Scale
                if (transform.LocalScale.IsDirty() || parentTransform.GlobalScale.IsDirty()) {
                    transform.GlobalScale =
                        parentTransform.GlobalScale.Get() * transform.LocalScale.Get();
                }

                if (transform.GlobalScale.IsDirty() || parentTransform.GlobalScale.IsDirty()) {
                    transform.LocalScale =
                        transform.GlobalScale.Get() / parentTransform.GlobalScale.Get();
                }
            }
        }
        else {
            // Position
            if (transform.LocalPosition.IsDirty()) {
                transform.GlobalPosition = transform.LocalPosition;
            }

            if (transform.GlobalPosition.IsDirty()) {
                transform.LocalPosition = transform.GlobalPosition;
            }

            // Rotation
            if (transform.LocalEulerRotation.IsDirty()) {
                transform.GlobalEulerRotation = transform.LocalEulerRotation;
            }

            if (transform.GlobalEulerRotation.IsDirty()) {
                transform.LocalEulerRotation = transform.GlobalEulerRotation;
            }

            // Scale
            if (transform.LocalScale.IsDirty()) {
                transform.GlobalScale = transform.LocalScale;
            }

            if (transform.GlobalScale.IsDirty()) {
                transform.LocalScale = transform.GlobalScale;
            }
        }
    }
}
