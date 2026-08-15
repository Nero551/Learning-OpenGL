#pragma once
#include "../Uniform.hpp"
#include "Math/Vector/Vector4.hpp"

namespace E {
struct Vector4Uniform : Uniform {
    M::Vector4 Value;

    Vector4Uniform(const std::string& name, const M::Vector4& value) : Uniform(name), Value(value) {}

    void Upload(int location) override {
        glUniform4fv(location, 1, &Value.x);
    }
};
}
