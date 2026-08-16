#include "Shader.hpp"
#include <OpenGL.hpp>
#include "Utilities/Logger.hpp"


#include "../Uniforms/FloatUniform.hpp"

namespace E {
void Shader::AssignSource(ShaderSource& source) {
    for (auto& existing : Sources) {
        if (existing->GetStage() == source.GetStage()) {
            // E::U::Logger::Error("Shader: " + Name + " Duplicate Shader Stage.");
            return;
        }
    }

    Sources.emplace_back(&source);
}

std::vector<U::CheckedPtr<ShaderSource>>& Shader::GetSources() {
    return Sources;
}

Shader::Shader(const std::string& name) : Resource(name) {}

Shader::~Shader() {
    glDeleteProgram(Id);
}

void Shader::Reload() {
    for (auto& source : Sources) {
        source->Reload();
    }

    UniformLocations.clear();
    glDeleteProgram(Id);
    Id = 0;
}

unsigned int Shader::GetId() const {
    return Id;
}

void Shader::Use() {
    if (!IsProgramCreated()) {
        CreateProgram();
    }

    glUseProgram(Id);
    UploadUniforms();
}

bool Shader::IsProgramCreated() const {
    return Id != 0;
}

void Shader::UploadUniforms() {
    for (auto& [location, uniform] : PendingUniforms) {
        uniform->Upload(location);
    }
}

int Shader::GetUniformLocation(const std::string& name) {
    int location;

    if (UniformLocations.contains(name)) {
        location = static_cast<int>(UniformLocations[name]);
    }
    else {
        location = glGetUniformLocation(Id, name.c_str());

        if (location == -1) {
            // E::U::Logger::Warning("Shader: " + Name + " Uniform Not Found: " + name);
        }

        UniformLocations[name] = location;
    }
    return location;
}


void Shader::CreateProgram() {
    if (Sources.empty()) {
        U::Logger::Warning("Shader Program:" + Name + " Has No Sources");
        return;
    }

    Id = glCreateProgram();

    for (const auto& source : Sources) {
        if (!source->IsCompiled()) {
            source->Compile();
        }
        glAttachShader(Id, source->GetId());
    }
    glLinkProgram(Id);

    int success;
    char infoLog[512];
    glGetProgramiv(Id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(Id, 512, nullptr, infoLog);
        U::Logger::Error(std::string("Shader Program: " + Name + " Linking Failed: ") + infoLog);
    }
}
} // namespace E
