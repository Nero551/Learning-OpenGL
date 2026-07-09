#include "Renderer.hpp"
#include "OpenGL.hpp"
#include "Core/Engine.hpp"

void Renderer::Start() { glEnable(GL_DEPTH_TEST); }

void Renderer::Update(double dt) {}

void Renderer::Render() {
  for (Object object : Objects) {
    object.Draw(Engine::Instance->camera.GetViewMatrix(), Engine::Instance->camera.GetProjectionMatrix());
  }
}

void Renderer::Stop() {}