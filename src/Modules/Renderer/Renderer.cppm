module;

export module Renderer;

import Math;
import Module;
import World;

Matrix4 view = Matrix4::Identity;
Matrix4 projection = Matrix4::Perspective(Math::DegToRad(45), 800.0f / 800.0f, 0.1, 100);

export struct Renderer : Module {
  void Start() override { view = view.Translate({0, 0, -3}); }
  void Update(double dt) override {}
  void Stop() override {}
  void Render() {
    for (Object object : Objects) {
      object.Draw(view, projection);
    }
  }
};
