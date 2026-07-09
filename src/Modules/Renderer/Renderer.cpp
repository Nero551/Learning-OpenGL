#include "Renderer.hpp"
#include "Core/Engine.hpp"

void Renderer::Start() {}

void Renderer::Update(double dt) {}

void Renderer::Render() {
  for (Object object : Objects) {
    object.Draw(Engine::Instance->Camera.GetViewMatrix(), Engine::Instance->Camera.GetProjectionMatrix());
  }
}

void Renderer::Stop() {}