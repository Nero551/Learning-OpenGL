#pragma once

#include <vector>
#include "Core/Module.hpp"
#include "Resources/Material.hpp"
#include "Resources/Mesh.hpp"

struct Renderer : Module {

  void Start() override;
  void Update(double dt) override;
  void Stop() override;
  void Render() override;

  void Draw(Mesh &mesh, Material &material, const Matrix4 &modelMatrix, const Matrix4 &viewMatrix,
    const Matrix4 &projectionMatrix);
};