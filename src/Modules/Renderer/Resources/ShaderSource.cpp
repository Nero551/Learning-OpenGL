#include "ShaderSource.hpp"
#include <string>
#include <unordered_set>

#include "Core/OuterCore/Resource.hpp"
#include "Utilities/Logger.hpp"
#include "Utilities/FileSystem/FileSystem.hpp"

void ShaderSource::Preprocess() {
    Code.insert(0, "#" + Version + "\n");

    Includes.clear();
    std::unordered_set<std::string> includesProcessing;
    PreprocessIncludes(Path, Code, includesProcessing);
}


//TODO- replace with line by line parsing
void ShaderSource::PreprocessIncludes(const std::string& path, std::string& code,
    std::unordered_set<std::string>& includesProcessing) {
    const std::string include = "#include \"";
    auto pos = code.find(include);

    while (pos != std::string::npos) {
        const auto start = pos + include.length();
        const auto end = code.find('\"', start);
        const auto directory = code.substr(start, end - start);
        auto includePath = std::filesystem::path(path).parent_path() / directory;

        if (!includePath.empty()) {
            //Check If Is Already Included
            if (Includes.contains(includePath)) {
                code.replace(pos, end - pos + 1, "");
            }
            else {
                //Check Circular Include
                if (!includesProcessing.insert(includePath).second) {
                    Logger::Fatal("Circular Include: " + includePath.string() + " | In Shader: " + path);
                }

                //Recursively Include
                std::string includeCode = FileSystem::ReadFile(includePath);
                PreprocessIncludes(includePath, includeCode, includesProcessing);

                code.replace(pos, end - pos + 1, includeCode);
                Includes.insert(includePath);

                includesProcessing.erase(includePath);
            }
        }
        pos = code.find(include, pos + 1);
    }
}

ShaderSource::ShaderSource(const std::string& name, const std::string& path, ShaderStage stage,
    const std::string& version) : Resource(name), Path(path), Version(version), Stage(stage) {
    Code = FileSystem::ReadFile(path);

    if (Code.empty()) {
        return;
    }
    Preprocess();
    // FileSystem::WriteFile("Assets/" + name + ".txt", Code);

    const char* string = Code.c_str();

    Id = glCreateShader(static_cast<int>(Stage));
    glShaderSource(Id, 1, &string, nullptr);
    glCompileShader(Id);

    int success;
    char infoLog[512];
    glGetShaderiv(Id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(Id, 512, nullptr, infoLog);
        Logger::Error(std::string("Shader: ") + infoLog);
    }
}

ShaderSource::~ShaderSource() {
    glDeleteShader(Id);
}

unsigned int ShaderSource::GetId() const {
    return Id;
}

ShaderStage ShaderSource::GetStage() {
    return Stage;
}
