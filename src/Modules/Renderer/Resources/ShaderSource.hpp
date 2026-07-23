#pragma once

#include <string>
#include <unordered_set>

#include "Core/OuterCore/Resource.hpp"
#include "Modules/Renderer/Enums/ShaderStage.hpp"

struct ShaderSource : Resource {
    std::string Path;
    std::string Code = "";

    ShaderSource(const std::string& name, const std::string& path, const ShaderStage stage);
    ~ShaderSource() override;
    unsigned int GetId();
    ShaderStage GetStage();

private:
    unsigned int Id = 0;
    ShaderStage Stage;
    void Preprocess();
    void PreprocessIncludes(const std::string& path, std::string& code,
        std::unordered_set<std::string>& includesProcessing);
    std::unordered_set<std::string> Includes;
};
