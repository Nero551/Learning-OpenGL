#include "Core/Engine.hpp"
#include <OpenGL.hpp>

int main() {

  glfwInit();
  Engine engine;
  Engine::Ins = &engine;

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