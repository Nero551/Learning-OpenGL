#pragma once

#include <string>
#include <unordered_set>

#include "Core/OuterCore/Resource.hpp"
#include "Modules/Renderer/Enums/ShaderStage.hpp"

namespace E {
/**
 * @brief Represents a shader source file and its OpenGL shader object.
 * Handles loading, preprocessing, and reloading of a shader source.
 */
struct ShaderSource : Resource {
    std::string Path;
    std::string Code;
    std::string Version = "version 330 core";

    //TODO- it would be really cool if i could have methods for adding code dynamically , like GenerateInt("MaxLights", 20)
    // and it adds it to the shader code

    ShaderSource(const std::string& name, const std::string& path, ShaderStage stage, std::string version = "version 330 core");

    ~ShaderSource() override;
    unsigned int GetId() const;
    ShaderStage GetStage();

    /** @brief Preprocesses the source, generates an OpenGL id, compiles the source a */
    void Compile();
    bool IsCompiled() const;
    /** @brief Reloads and preprocesses the shader source. */
    void Reload();

private:
    unsigned int Id = 0;
    ShaderStage Stage;
    /** @brief Paths of shader files included by this source. */
    std::unordered_set<std::string> Includes;
    void Preprocess();
    void PreprocessIncludes(const std::string& path, std::string& code, std::unordered_set<std::string>& includesProcessing);
};
}
