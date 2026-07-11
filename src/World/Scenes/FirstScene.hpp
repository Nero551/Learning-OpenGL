#pragma once
#include "Core/Engine.hpp"
#include "Core/Scene.hpp"

struct FirstScene : Scene {
   void Initialize() override {
      Camera &camera = CreateEntity<Camera>();
      camera.GetComponent<CameraComponent>().AspectRatio = Engine::Ins->Window.Width / Engine::Ins->Window.Height;
      SetActiveCamera(camera);
   }
};
