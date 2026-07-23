#pragma once
#include "Core/OuterCore/ECS/Entity.hpp"
#include "Modules/Renderer/Components/MaterialComponent.hpp"
#include "Modules/Renderer/Components/MeshComponent.hpp"
#include "World/Components/Transform3DComponent.hpp"

struct Axis : Entity {
    void Initialize() override {
        AddComponent<MeshComponent>();
        AddComponent<MaterialComponent>();
        AddComponent<Transform3DComponent>();
    }
};
