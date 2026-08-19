#pragma once
#include "../Uniform.hpp"
#include "Core/InnerCore/Engine.hpp"

namespace E {
struct FloatUniform : Uniform {
    float Value;

    FloatUniform(const std::string& name, const float value) : Uniform(name), Value(value) {
    }

    void Upload(const int location) override {
        glUniform1f(location, Value);
    }
};
} // namespace E
