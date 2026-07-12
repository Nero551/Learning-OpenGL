#include "Material.hpp"

#include "../Uniforms/FloatUniform.hpp"
#include "../Uniforms/IntUniform.hpp"
#include "../Uniforms/Vector3Uniform.hpp"
#include "../Uniforms/Vector4Uniform.hpp"
#include "Utilities/Services/LoggerService.hpp"

Material::Material(const std::string &name) : Resource(name) {}

void Material::Use() {
   GetShader().Use();

   GetShader().SetUniform(Vector3Uniform("Material.Ambient", Ambient));
   GetShader().SetUniform(Vector3Uniform("Material.Diffuse", Diffuse));
   GetShader().SetUniform(Vector3Uniform("Material.Specular", Specular));
   GetShader().SetUniform(FloatUniform("Material.Shininess", Shininess));
   GetShader().SetUniform(Vector4Uniform("Material.Color", MaterialColor));

   for (Texture *texture: Textures) {
      if (texture) {
         GetShader().SetUniform(IntUniform(texture->Name, texture->GetUnit()));
         texture->Bind();
      }
   }
}

void Material::AssignShader(struct Shader &shader) { Shader = &shader; }

Shader &Material::GetShader() {
   return *Shader;
}

void Material::AssignTexture(Texture &texture) {
   if (texture.GetUnit() >= Textures.size()) {
      LoggerService::Error("Texture out of bounds: " + texture.Name);
   }

   Textures[texture.GetUnit()] = &texture;
}
