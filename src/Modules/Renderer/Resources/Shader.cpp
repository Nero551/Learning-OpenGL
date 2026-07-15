#include <string>
#include "Utilities/Services/LoggerService.hpp"
#include <OpenGL.hpp>
#include "Utilities/FileSystem/FileSystem.hpp"
#include "Shader.hpp"

#include <ranges>

#include "../Uniforms/FloatUniform.hpp"

Shader::Shader(const std::string& name, const std::string& fragFilepath,
               const std::string& vertFilepath) : Resource(name)
{
    std::string fragCode = FileSystem::ReadFile(fragFilepath);
    std::string vertCode = FileSystem::ReadFile(vertFilepath);
    const char* fragSource = fragCode.c_str();
    const char* vertSource = vertCode.c_str();

    unsigned int fragShader = CreateFragShader(fragSource);
    unsigned int vertShader = CreateVertShader(vertSource);

    Id = CreateShaderProgram(fragShader, vertShader);

    //* Cleanup
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
}

Shader::~Shader()
{
    glDeleteProgram(Id);
}

unsigned int Shader::GetId() const { return Id; }

void Shader::Use()
{
    glUseProgram(Id);
    UploadUniforms();
}

void Shader::UploadUniforms() { for (auto& [location, uniform] : PendingUniforms) { uniform->Upload(location); } }

int Shader::GetUniformLocation(const std::string& name)
{
    int location;

    if (UniformLocations.contains(name)) { location = UniformLocations[name]; }
    else
    {
        location = glGetUniformLocation(Id, name.c_str());

        if (location == -1)
        {
            // LoggerService::Warning("Uniform Not Found: " + name);
        }

        UniformLocations[name] = location;
    }
    return location;
}


unsigned int Shader::CreateShaderProgram(unsigned int fragShader, unsigned int vertShader)
{
    unsigned int id = glCreateProgram();
    glAttachShader(id, vertShader);
    glAttachShader(id, fragShader);
    glLinkProgram(id);

    int success;
    char infoLog[512];
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(id, 512, nullptr, infoLog);
        LoggerService::Error(std::string("Shader program linking failed: ") + infoLog);
    }

    return id;
}

unsigned int Shader::CreateFragShader(const char* fragSource)
{
    unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragSource, nullptr);
    glCompileShader(fragShader);

    int success;
    char infoLog[512];
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragShader, 512, nullptr, infoLog);
        LoggerService::Error(std::string("Fragment Shader: ") + infoLog);
    }

    return fragShader;
}

unsigned int Shader::CreateVertShader(const char* vertSource)
{
    unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vertSource, nullptr);
    glCompileShader(vertShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertShader, 512, nullptr, infoLog);
        LoggerService::Error(std::string("Vertex Shader: ") + infoLog);
    }

    return vertShader;
}
