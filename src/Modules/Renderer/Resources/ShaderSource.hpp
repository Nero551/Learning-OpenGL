#pragma once

#include <string>
#include <unordered_set>

#include "Core/OuterCore/Resource.hpp"
#include "Modules/Renderer/Enums/ShaderStage.hpp"

struct ShaderSource : Resource {
    std::string Path;
    std::string Code;
    std::string Version = "version 330 core";

    ShaderSource(const std::string& name, const std::string& path, ShaderStage stage,
        const std::string& version = "version 330 core");
    ~ShaderSource() override;
    unsigned int GetId() const;
    ShaderStage GetStage();

private:
    unsigned int Id = 0;
    ShaderStage Stage;
    void Preprocess();
    void PreprocessIncludes(const std::string& path, std::string& code,
        std::unordered_set<std::string>& includesProcessing);
    std::unordered_set<std::string> Includes;
};
