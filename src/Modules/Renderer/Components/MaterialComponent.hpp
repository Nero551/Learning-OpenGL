#pragma once
#include "Core/Component.hpp"
#include "Modules/Renderer/Resources/Material.hpp"

struct MaterialComponent : Component {
  Material *Material = nullptr;
};