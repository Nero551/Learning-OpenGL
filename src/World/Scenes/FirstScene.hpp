#pragma once
#include "Core/OuterCore/Scene.hpp"

struct FirstScene : Scene {
    FirstScene();

    void FixedUpdate(double fdt) override;
};
