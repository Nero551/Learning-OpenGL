#pragma once

#include "Core/OuterCore/Scene.hpp"

namespace E {
struct AssimpScene : Scene {
    AssimpScene(const std::string& filepath);
};
} // namespace E
