#pragma once

#include <vector>
#include "Core/Module.hpp"
#include "World/Object.hpp"

struct Renderer : Module {
  std::vector<Object> Objects;

  void Start() override;
  void Update(double dt) override;
  void Stop() override;
  void Render() override;
};