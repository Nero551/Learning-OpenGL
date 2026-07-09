#include "Renderer.hpp"
#include "Core/Engine.hpp"

void Renderer::Start() {}

void Renderer::Update(double dt) {}

void Renderer::Render() {
  for (Object object : Objects) {
    object.Draw(Engine::Instance->World.ActiveScene->ActiveCamera->GetViewMatrix(),
      Engine::Instance->World.ActiveScene->ActiveCamera->GetProjectionMatrix());
  }
}

void Renderer::Stop() {}