#include "Core.h"
#include <GLFW/glfw3.h>
#include <iostream>

int main() {

  glfwInit();
  Engine engine;

  glEnable(GL_DEPTH_TEST);

  engine.Start();
  engine.Running = true;

  while (!engine.window.ShouldClose()) {
    engine.BeginFrame();

    engine.Update();
    engine.Render();

    engine.EndFrame();
  }

  engine.Stop();
  glfwTerminate();
  return 0;
}
