#pragma once
#include "OpenGL.hpp"

#include "Utilities/Logger.hpp"

namespace E {
struct GLFWContext {
    GLFWContext() {
        glfwSetErrorCallback([](int error, const char* description) {
            U::Logger::Error("[GLFW]", error, ": ", description);
        });
        glfwInit();
    }

    ~GLFWContext() {
        glfwTerminate();
    }
};
}
