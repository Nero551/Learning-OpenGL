#pragma once
#include "../Uniform.hpp"
#include "Core/Engine.hpp"

struct FloatUniform : Uniform
{
    float Value;

    FloatUniform(const std::string& name, float value) : Uniform(name), Value(value) {}

    void Upload(int location) override
    {
        glUniform1f(location, Value);
    }
};
