#pragma once
#include "Core/OuterCore/ECS/Component.hpp"
#include "Modules/Renderer/Resources/Material.hpp"
#include "Utilities/CheckedPtr.hpp"

struct MaterialComponent : Component {
    CheckedPtr<Material> Material{"Material Component Has No Material Assigned"};
};
