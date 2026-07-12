#pragma once

#include "Core/Component.hpp"
#include "Utilities/Math/Vector/Vector3.hpp"

struct LightComponent : Component {
   Vector3 Color = {1};
   Vector3 Ambient = {1};
   Vector3 Diffuse = {1};
   Vector3 Specular = {1};
};
