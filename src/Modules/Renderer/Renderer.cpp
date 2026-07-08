#include "Renderer.hpp"
#include "OpenGL.hpp"
#include "Utilities/Math/MathUtils.hpp"

// TODO- view and projection should be owned by the camera.

Matrix4 view = Matrix4::Identity;
Matrix4 projection = Matrix4::Perspective(Math::DegToRad(45), 800.0f / 800.0f, 0.1, 100);

void Renderer::Start() {
  glEnable(GL_DEPTH_TEST);
  view = view.Translate({0, 0, -3});
}

void Renderer::Update(double dt) {}

void Renderer::Render() {
  for (Object object : Objects) {
    object.Draw(view, projection);
  }
}

void Renderer::Stop() {}