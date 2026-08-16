#pragma once
#include "../Uniform.hpp"
#include "Core/InnerCore/Engine.hpp"

namespace E {
struct Vector3Uniform : Uniform {
    M::Vector3 Value;

    Vector3Uniform(const std::string& name, const M::Vector3& value) : Uniform(name), Value(value) {
    }

    void Upload(int location) override {
        glUniform3fv(location, 1, &Value.x);
    }
};
} // namespace E
