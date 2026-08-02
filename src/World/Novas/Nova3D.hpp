#pragma once
#include "World/Components/Transform3DComponent.hpp"
#include "Nova.hpp"

namespace E {
struct Nova3D : Nova {
    void Initialize() override {
        Nova::Initialize();
        AddComponent<Transform3DComponent>();
    }
};
}
