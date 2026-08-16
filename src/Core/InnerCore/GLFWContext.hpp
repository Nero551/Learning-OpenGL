#pragma once
#include "OpenGL.hpp"
#include "Utilities/Logger.hpp"

namespace E {
/** @brief Handles initialization and termination of GLFW.
 * Created by Engine, constructed first, deconstructed last. that way it
 * prevents GLFW errors
 */
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
} // namespace E
