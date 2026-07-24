#pragma once

#include "Core/OuterCore/Scene.hpp"
#include "World/Novas/MeshInstance3D.hpp"

struct CalculusTesting : Scene {
    CalculusTesting();
    void FixedUpdate(double fdt) override;

private:
    void Plot(Vector3 vec3);
    MeshInstance3D& CreatePoint();
};
