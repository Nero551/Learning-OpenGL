#pragma once

#include "World/World.hpp"
#include <vector>
#include "Core/Module.hpp"

struct Renderer : Module {
  std::vector<Object> Objects;

  void Start() override;
  void Update(double dt) override;
  void Stop() override;
  void Render() override;
};