#pragma once
#include "../Components/LightComponent.hpp"
#include "../Components/MaterialComponent.hpp"
#include "../Components/MeshComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "Core/Entity.hpp"

struct Light : Entity
{
    void Initialize() override
    {
        AddComponent<MeshComponent>();
        AddComponent<TransformComponent>();
        AddComponent<MaterialComponent>();
        AddComponent<LightComponent>();
    }
};
