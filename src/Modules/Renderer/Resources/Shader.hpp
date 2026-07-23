#pragma once

#include <unordered_set>

#include "../Uniform.hpp"
#include "Core/OuterCore/Resource.hpp"

template <typename T>concept UniformType = std::derived_from<T, Uniform>;

struct Shader : Resource {
    Shader(const std::string& name, const std::string& fragFilepath, const std::string& vertFilepath);

    ~Shader() override;

    unsigned int GetId() const;

    void Use();

    template <UniformType T> void SetUniform(const T& uniform) {
        PendingUniforms[GetUniformLocation(uniform.Name)] = std::make_unique<T>(uniform);
    }

private:
    unsigned int Id;
    std::unordered_map<std::string, unsigned int> UniformLocations;
    std::unordered_map<int, std::unique_ptr<Uniform>> PendingUniforms;
    std::string FragmentPath;
    std::string VertexPath;
    std::unordered_set<std::string> Includes;

    unsigned int CreateShaderProgram(unsigned int fragShader, unsigned int vertShader);

    unsigned int CreateVertShader(const char* vertSource);

    unsigned int CreateFragShader(const char* fragSource);

    int GetUniformLocation(const std::string& name);

    void UploadUniforms();

    void Preprocess(std::string& fragCode, std::string& vertCode);
    void PreprocessIncludes(const std::string& path, std::string& code,
        std::unordered_set<std::string>& includesProcessing);
};
