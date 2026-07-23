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

        //TODO- allow for ability to modify both local and global , do this by using "Dirty".
        //* need to detect both local and global changes for both entity and its parent

        if (entity->HasParent() && transform.InheritTransform == true) {
            auto& parent = entity->GetParent();
            if (parent.HasComponent<Transform3DComponent>()) {
                auto& parentTransform = parent.GetComponent<Transform3DComponent>();


                if (transform.LocalPosition.IsDirty() || parentTransform.GlobalPosition.IsDirty()) {
                    Logger::Info(transform.LocalPosition.IsDirty());
                    transform.GlobalPosition = parentTransform.GlobalPosition.Get() + transform.LocalPosition.Get();
                }

                if (transform.GlobalPosition.IsDirty() || parentTransform.GlobalPosition.IsDirty()) {
                    transform.LocalPosition = transform.GlobalPosition.Get() - parentTransform.GlobalPosition.Get();
                }

                transform.GlobalEulerRotation = parentTransform.GlobalEulerRotation + transform.LocalEulerRotation;
                transform.GlobalScale = parentTransform.GlobalScale * transform.LocalScale;
            }
        }
        else {
            if (transform.LocalPosition.IsDirty()) {
                transform.GlobalPosition = transform.LocalPosition;
            }
            if (transform.GlobalPosition.IsDirty()) {
                transform.LocalPosition = transform.GlobalPosition;
            }

            transform.GlobalEulerRotation = transform.LocalEulerRotation;
            transform.GlobalScale = transform.LocalScale;
        }
    }
}
