#pragma once
#include "Nova3D.hpp"
#include "Modules/Renderer/Components/CameraComponent.hpp"

struct Camera : Nova3D {
    void Initialize() override {
        Nova3D::Initialize();
        AddComponent<CameraComponent>();
    }
};
