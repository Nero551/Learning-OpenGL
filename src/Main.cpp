#include <OpenGL.hpp>

#include "Core/InnerCore/Engine.hpp"

int main() {
    glfwInit();
    Engine engine;
    Engine::Ins = &engine;
    ServiceStore services;
    ServiceStore::Ins = &services;
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
