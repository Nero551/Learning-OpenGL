#include "Core.hpp"
#include <OpenGL.hpp>
#include <iostream>

int main() {

  glfwInit();
  Engine engine;
  Engine::Instance = &engine;

  glEnable(GL_DEPTH_TEST);

  engine.Start();
  engine.Running = true;

  while (!engine.Running) {
    engine.BeginFrame();

    engine.Update();
    engine.Render();

    engine.EndFrame();
  }

  engine.Stop();
  return 0;
}
