#include "Engine.hpp"

#include <OpenGL.hpp>
#include <ranges>

#include "../Modules/Renderer/Renderer.hpp"
#include "Core/World.hpp"
#include "Modules/Input/Input.hpp"

Engine::Engine() : Window(1000, 800, "Plus Ultra") { Running = true; }

/*
  ? engine owns Scenes, or world owns scenes, idc , scenes own entities, entities own components. system run on scene.
  ? 6 things. Modules, Resources , Entities , Components , Systems, Utilities

  ? Modules - big chunks of all the following grouped together. like renderer, input, physics, asset loading
  ? Resources - things that don't really exist, shaders, textures , meshes, etc.
  ? Entities - just ids and contain components.
  ? Components - just data, no logic.
  ? Systems - loop over entities in a scene and does logic on components. can do logic on its own as well.
  ? Utilities - it's in the name.
*/

Engine *Engine::Ins = nullptr;

void Engine::AddModules() {
   AddModule<Renderer>();
   AddModule<Input>();
}

void Engine::Start() {
   AddModules();
   World.Start();

   for (auto &module: Modules | std::views::values) {
      module->Start();
   }

   GetModule<Input>().SetMouseMode(MouseMode::Disabled);
}

void Engine::Update() {
   Time = glfwGetTime();
   World.Update(DeltaTime);

   if (GetModule<Input>().IsKeyHeld(Key::Escape)) {
      Running = false;
      Window.Close();
   }

   if (GetModule<Input>().IsKeyReleased(Key::Q)) {
      if (GetModule<Input>().GetMouseMode() == MouseMode::Disabled) {
         GetModule<Input>().SetMouseMode(MouseMode::Normal);
      } else {
         GetModule<Input>().SetMouseMode(MouseMode::Disabled);
      }
   }

   for (auto &module: Modules | std::views::values) {
      module->Update(DeltaTime);
   }
}

void Engine::Stop() {
   World.Stop();

   for (auto &module: Modules | std::views::values) {
      module->Stop();
   }

   glfwTerminate();
}

void Engine::Render() {
   for (auto &module: Modules | std::views::values) {
      module->Render();
   }
}

void Engine::BeginFrame() {
   Window.PollEvents();
   glClearColor(0.1, 0.15, 0.2, 1);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   World.BeginFrame(DeltaTime);

   for (auto &module: Modules | std::views::values) {
      module->BeginFrame(DeltaTime);
   }
}

void Engine::EndFrame() {
   const float currentFrame = Time;
   DeltaTime = currentFrame - LastFrame;
   LastFrame = currentFrame;
   Window.SwapBuffers();

   World.EndFrame(DeltaTime);

   for (auto &module: Modules | std::views::values) {
      module->EndFrame(DeltaTime);
   }
}
