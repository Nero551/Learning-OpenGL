#pragma once
#include "Modules/Renderer/Components/Transform3DComponent.hpp"
#include "Nova.hpp"

struct Nova3D : Nova {
    void Initialize() override {
        Nova::Initialize();
        AddComponent<Transform3DComponent>();
    }
};
