#pragma once

#include "Core/OuterCore/Resource.hpp"
#include "Math/Vector/Vector3.hpp"
#include "Math/Vector/Vector4.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Utilities/CheckedPtr.hpp"

namespace E {
struct Material : Resource {
    static constexpr int MaxCustomTextures = 8;
    U::CheckedPtr<Shader> Shader{"Material Has No Shader Assigned"};

    M::Vector4 Color = {0.5};
    M::Vector3 Ambient = {1};
    M::Vector3 Diffuse = {0.7};
    M::Vector3 Specular = {0.7};
    M::Vector3 Emission = {0};
    float Shininess = 32;

    U::CheckedPtr<Texture> DiffuseMap;
    U::CheckedPtr<Texture> SpecularMap;
    U::CheckedPtr<Texture> EmissionMap;


    Material(const std::string& name);

    void AssignTexture(Texture& texture, unsigned int slot);

    void Use();

protected:
    std::array<U::CheckedPtr<Texture>, MaxCustomTextures> CustomTextures = {};

    void SetProperties() const;
};
} // namespace E
