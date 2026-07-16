#pragma once
#include "Nova3D.hpp"
#include "Modules/Renderer/Components/LightComponent.hpp"
#include "Modules/Renderer/Components/MaterialComponent.hpp"
#include "Modules/Renderer/Components/MeshComponent.hpp"

struct Light : Nova3D {
    void Initialize() override {
        Nova3D::Initialize();
        AddComponents<MeshComponent, MaterialComponent, LightComponent>();
    }
};
