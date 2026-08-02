#pragma once
#include "Nova3D.hpp"
#include "Modules/Renderer/Components/CameraComponent.hpp"

namespace E {
struct Camera : Nova3D {
    void Initialize() override {
        Nova3D::Initialize();
        AddComponent<CameraComponent>();
    }
};
}
