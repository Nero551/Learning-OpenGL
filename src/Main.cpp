#include <OpenGL.hpp>

#include "Core/InnerCore/Engine.hpp"
#include "Utilities/Math/Quaternion.hpp"

void Testing() {
    Quaternion q1 = {1, 1, 1, 1};
    Quaternion q2 = {1, 0, 0, 1};

    Logger::Info(q2);
}

int main() {
    Testing();
    return 0;

    glfwInit();
    Engine engine;
    ServiceStore services;

    engine.Start();

    double accumulator = 0;

    while (engine.Running) {
        engine.BeginFrame();

        accumulator += engine.DeltaTime;
        accumulator = std::min(accumulator, 0.25);

        while (accumulator >= engine.FixedDeltaTime) {
            engine.FixedUpdate();
            accumulator -= engine.FixedDeltaTime;
        }

        engine.Update();
        engine.Render();

        engine.EndFrame();
    }

    engine.Stop();
    return 0;
}
