#pragma once

#include "Core/Module.hpp"

struct Renderer : Module {

  void Start() override;
  void Update(double dt) override;
  void Stop() override;
  void Render() override;
};