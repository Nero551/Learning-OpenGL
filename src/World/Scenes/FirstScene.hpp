#pragma once
#include "Core/OuterCore/Scene.hpp"

namespace E {
struct FirstScene : Scene {
    FirstScene();

    void FixedUpdate(double fdt) override;
};
}
