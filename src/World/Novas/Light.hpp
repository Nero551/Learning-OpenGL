#pragma once
#include "Nova3D.hpp"
#include "Modules/Renderer/Components/LightComponent.hpp"

namespace E {
struct Light : Nova3D {
    void Initialize() override {
        Nova3D::Initialize();
        AddComponents<LightComponent>();
    }
};
}
