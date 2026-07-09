#include "Renderer.hpp"
#include "Core/Engine.hpp"

void Renderer::Start() {}

void Renderer::Update(double dt) {}

void Renderer::Render() {
  for (Object object : Objects) {
    object.Draw(Engine::Instance->World.Camera.GetViewMatrix(), Engine::Instance->World.Camera.GetProjectionMatrix());
  }
}

void Renderer::Stop() {}