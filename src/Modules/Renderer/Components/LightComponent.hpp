#pragma once

#include "../Enums/LightType.hpp"
#include "Core/OuterCore/ECS/Component.hpp"
#include "Utilities/Math/Vector/Vector3.hpp"

namespace E {
struct LightComponent : Component {
    LightType Type = LightType::Directional;
    Vector3 Color = {1};
    Vector3 Ambient = {0.8};
    Vector3 Diffuse = {1};
    Vector3 Specular = {1};

    float Intensity = 1;
    float Constant = 1.0f;
    float Linear = 0.009f;
    float Quadratic = 0.032f;
    float InnerCutOff = Math::Rad(7.5);
    float OuterCutOff = Math::Rad(17.5);
};
}
