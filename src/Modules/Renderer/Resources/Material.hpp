#pragma once

#include "Core/OuterCore/Resource.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Utilities/Math/Vector/Vector3.hpp"
#include "Utilities/Math/Vector/Vector4.hpp"
#include "Utilities/CheckedPtr.hpp"

namespace E {
struct Material : Resource {
    static constexpr int MaxCustomTextures = 8;
    CheckedPtr<Shader> Shader{"Material Has No Shader Assigned"};

    Vector4 Color = {0.5};
    Vector3 Ambient = {1};
    Vector3 Diffuse = {0.7};
    Vector3 Specular = {0.7};
    Vector3 Emission = {0};
    float Shininess = 32;

    CheckedPtr<Texture> DiffuseMap;
    CheckedPtr<Texture> SpecularMap;
    CheckedPtr<Texture> EmissionMap;


    Material(const std::string& name);

    void AssignTexture(Texture& texture, unsigned int slot);

    void Use();

protected:
    std::array<CheckedPtr<Texture>, MaxCustomTextures> CustomTextures = {};

    void SetProperties() const;
};
}
