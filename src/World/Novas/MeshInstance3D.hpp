#pragma once
#include "Modules/Renderer/Components/MeshComponent.hpp"
#include "Modules/Renderer/Components/MaterialComponent.hpp"
#include "Nova3D.hpp"

struct MeshInstance3D : Nova3D {
    void Initialize() override {
        Nova3D::Initialize();
        AddComponents<MeshComponent, MaterialComponent>();
    }
};
