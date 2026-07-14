#pragma once
#include "../Uniform.hpp"
#include "OpenGL.hpp"
#include "Utilities/Math/Matrix/Matrix4.hpp"

struct Matrix3Uniform : Uniform
{
    Matrix3 Value;

    Matrix3Uniform(const std::string& name, const Matrix3& value) : Uniform(name), Value(value) {}

    void Upload(int location) override
    {
        glUniformMatrix3fv(location, 1, GL_TRUE, *Value.m);
    }
};
