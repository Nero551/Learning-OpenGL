#include "Material.hpp"

#include "Utilities/Services/LoggerService.hpp"

Material::Material(const class Shader &shader) : Shader(shader) {}

void Material::Use() {
  Shader.Use();

  for (Texture texture : Textures) {
    Shader.SetInt(texture.Name, texture.Unit);
    texture.Bind();
  }
}

void Material::AssignTexture(const Texture &texture) { Textures.push_back(texture); }