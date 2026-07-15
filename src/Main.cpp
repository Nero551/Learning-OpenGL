#include <OpenGL.hpp>

#include "Core/InnerCore/Engine.hpp"

int main() {
    glfwInit();
    Engine engine;
    Engine::Ins = &engine;
    ServiceStore services;
    ServiceStore::Ins = &services;
    engine.Start();

    while (engine.Running) {
        engine.BeginFrame();

        engine.Update();
        engine.Render();

        engine.EndFrame();
    }

    engine.Stop();
    return 0;
}
