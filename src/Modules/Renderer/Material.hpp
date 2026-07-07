#pragma once

#include "Shader.hpp"
#include "Texture.hpp"

struct Material {
  Shader Shader;
  Texture Texture0;

  Material(class Shader shader, Texture texture);

  void Use();
};