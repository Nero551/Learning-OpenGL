#include "Material.hpp"

#include "../Uniforms/FloatUniform.hpp"
#include "../Uniforms/IntUniform.hpp"
#include "../Uniforms/Vector3Uniform.hpp"
#include "../Uniforms/Vector4Uniform.hpp"
#include "Utilities/Services/LoggerService.hpp"

Material::Material(const std::string &name) :
   Resource(name) {}

void Material::SetProperties() {
   Shader->SetUniform(Vector3Uniform("Material.Ambient", Ambient));
   Shader->SetUniform(Vector3Uniform("Material.Diffuse", Diffuse));
   Shader->SetUniform(Vector3Uniform("Material.Specular", Specular));
   Shader->SetUniform(FloatUniform("Material.Shininess", Shininess));
   Shader->SetUniform(Vector4Uniform("Material.Color", Color));
}

void Material::Use() {
   SetProperties();
   Shader->Use();

   for (Texture *texture: Textures) {
      if (texture) {
         Shader->SetUniform(IntUniform(texture->Name, texture->GetUnit()));
         texture->Bind();
      }
   }
}

void Material::AssignTexture(Texture &texture) {
   if (texture.GetUnit() >= Textures.size()) {
      LoggerService::Error("Texture out of bounds: " + texture.Name);
   }

   Textures[texture.GetUnit()] = &texture;
}
