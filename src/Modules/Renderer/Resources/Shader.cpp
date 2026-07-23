#include "Utilities/Logger.hpp"
#include <OpenGL.hpp>
#include "Utilities/FileSystem/FileSystem.hpp"
#include "Shader.hpp"


#include "../Uniforms/FloatUniform.hpp"

void Shader::AssignSource(ShaderSource& source) {
    for (auto& existing : Sources) {
        if (existing->GetStage() == source.GetStage()) {
            Logger::Error("Duplicate Shader Stage.");
            return;
        }
    }

    Sources.emplace_back(&source);
}

Shader::Shader(const std::string& name) : Resource(name) {}

Shader::~Shader() {
    glDeleteProgram(Id);
}

unsigned int Shader::GetId() const {
    return Id;
}

void Shader::Use() {
    if (Id == 0) {
        CreateProgram();
    }

    glUseProgram(Id);
    UploadUniforms();
}

void Shader::UploadUniforms() {
    for (auto& [location, uniform] : PendingUniforms) {
        uniform->Upload(location);
    }
}

int Shader::GetUniformLocation(const std::string& name) {
    int location;

    if (UniformLocations.contains(name)) {
        location = UniformLocations[name];
    }
    else {
        location = glGetUniformLocation(Id, name.c_str());

        if (location == -1) {
            // LoggerService::Warning("Uniform Not Found: " + name);
        }

        UniformLocations[name] = location;
    }
    return location;
}


void Shader::CreateProgram() {
    if (Sources.empty()) {
        Logger::Warning("Shader Has No Sources");
        return;
    }

    Id = glCreateProgram();

    for (const auto& source : Sources) {
        glAttachShader(Id, source->GetId());
    }
    glLinkProgram(Id);

    int success;
    char infoLog[512];
    glGetProgramiv(Id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(Id, 512, nullptr, infoLog);
        Logger::Error(std::string("Shader program linking failed: ") + infoLog);
    }
}
