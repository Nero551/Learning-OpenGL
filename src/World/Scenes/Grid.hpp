#pragma once

#include "Core/OuterCore/Scene.hpp"
#include "Math/Vector/Vector3.hpp"

namespace E {
struct Grid : Scene {
    Grid();

private:
    void CreateGridLine(M::Vector3 rotation, M::Vector3 position);
};
} // namespace E
