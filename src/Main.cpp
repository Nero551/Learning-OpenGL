#include <OpenGL.hpp>

#include "Core/Engine.hpp"

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
