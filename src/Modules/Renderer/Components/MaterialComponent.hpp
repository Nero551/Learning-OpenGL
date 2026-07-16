#pragma once
#include "Core/OuterCore/Component.hpp"
#include "Modules/Renderer/Resources/Material.hpp"
#include "Utilities/CheckedPtr.hpp"

struct MaterialComponent : Component {
    CheckedPtr<Material> Material{"Material Component Has No Material Assigned"};
};
