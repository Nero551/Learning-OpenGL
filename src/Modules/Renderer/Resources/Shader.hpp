#pragma once

#include "ShaderSource.hpp"
#include "../Uniform.hpp"
#include "Core/OuterCore/Resource.hpp"
#include "Utilities/CheckedPtr.hpp"

template <typename T>concept UniformType = std::derived_from<T, Uniform>;

struct Shader : Resource {
    Shader(const std::string& name);

    ~Shader() override;

    unsigned int GetId() const;

    void Use();

    template <UniformType T> void SetUniform(const T& uniform) {
        PendingUniforms[GetUniformLocation(uniform.Name)] = std::make_unique<T>(uniform);
    }

    void AssignSource(ShaderSource& source);

private:
    unsigned int Id = 0;
    std::unordered_map<std::string, unsigned int> UniformLocations;
    std::unordered_map<int, std::unique_ptr<Uniform>> PendingUniforms;
    std::vector<CheckedPtr<ShaderSource>> Sources;

    void CreateProgram();

    int GetUniformLocation(const std::string& name);

    void UploadUniforms();
};
