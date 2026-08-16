#pragma once
#include "Core/OuterCore/ECS/Component.hpp"
#include "Modules/Renderer/Resources/Material.hpp"
#include "Utilities/CheckedPtr.hpp"

namespace E {
struct MaterialComponent : Component {
    U::CheckedPtr<Material> Material{"Material Component Has No Material Assigned"};
};
} // namespace E
