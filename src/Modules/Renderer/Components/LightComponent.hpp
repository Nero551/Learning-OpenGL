#pragma once

#include "../Enums/LightType.hpp"
#include "Core/OuterCore/ECS/Component.hpp"
#include "Utilities/Math/Vector/Vector3.hpp"

struct LightComponent : Component {
    LightType Type = LightType::Point;
    Vector3 Color = {1};
    Vector3 Ambient = {1};
    Vector3 Diffuse = {1};
    Vector3 Specular = {1};

    float Intensity = 1;
    float Constant = 1.0f;
    float Linear = 0.009f;
    float Quadratic = 0.032f;
    float InnerCutOff = Math::Radians(12.5);
    float OuterCutOff = Math::Radians(17.5);
};
