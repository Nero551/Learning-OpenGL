#pragma once
#include "Core/Component.hpp"
#include "Modules/Renderer/Resources/Material.hpp"
#include "Utilities/SafePtr.hpp"

struct MaterialComponent : Component {
   SafePtr<Material> Material{"Material Component Has No Material Assigned"};
};
