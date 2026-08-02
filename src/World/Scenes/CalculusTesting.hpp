#pragma once

#include "Core/OuterCore/Scene.hpp"
#include "World/Novas/MeshInstance3D.hpp"

namespace E {
struct CalculusTesting : Scene {
    CalculusTesting();
    void FixedUpdate(double fdt) override;

private:
    void Plot(Vector3 vec3, Vector4 col = {1, 1, 1, 1});
    MeshInstance3D& CreatePoint(Vector4 col);
};
}
