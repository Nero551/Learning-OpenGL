#pragma once

#include "Core/OuterCore/Resource.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Utilities/Math/Vector/Vector3.hpp"
#include "Utilities/Math/Vector/Vector4.hpp"
#include "Utilities/CheckedPtr.hpp"

struct Material : Resource {
    static constexpr int MaxTextures = 8;
    CheckedPtr<Shader> Shader{"Material Has No Shader Assigned"};

    Vector4 Color = {1};
    Vector3 Ambient = {1};
    Vector3 Diffuse = {1};
    Vector3 Specular = {1};
    Vector3 Emission = {0};
    float Shininess = 32;

    CheckedPtr<Texture> DiffuseMap;
    CheckedPtr<Texture> SpecularMap;
    CheckedPtr<Texture> EmissionMap;


    Material(const std::string& name);

    void AssignTexture(Texture& texture, unsigned int slot);

    void Use();

protected:
    std::array<CheckedPtr<Texture>, MaxTextures> CustomTextures{};

    void SetProperties();
};
