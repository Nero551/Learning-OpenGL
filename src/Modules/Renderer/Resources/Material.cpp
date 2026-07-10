#include "Material.hpp"

#include "Utilities/Services/LoggerService.hpp"

Material::Material(const std::string &name) : Name(name) {}

void Material::Use() {
  Shader->Use();

  for (Texture *texture : Textures) {
    Shader->SetInt(texture->Name, texture->Unit);
    texture->Bind();
  }
}

void Material::AssignShader(struct Shader &shader) { Shader = &shader; }

void Material::AssignTexture(Texture &texture) { Textures.push_back(&texture); }