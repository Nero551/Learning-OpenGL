#include "Material.hpp"

#include "../Uniforms/FloatUniform.hpp"
#include "../Uniforms/IntUniform.hpp"
#include "../Uniforms/Vector3Uniform.hpp"
#include "../Uniforms/Vector4Uniform.hpp"
#include "Utilities/Services/LoggerService.hpp"

Material::Material(const std::string &name) :
   Resource(name) {

   DiffuseMap = &Primitives::CreateWhiteTexture();
   SpecularMap = &Primitives::CreateWhiteTexture();
   EmissionMap = &Primitives::CreateWhiteTexture();

}

void Material::SetProperties() {
   Shader->SetUniform(Vector3Uniform("Material.Ambient", Ambient));
   Shader->SetUniform(Vector3Uniform("Material.Diffuse", Diffuse));
   Shader->SetUniform(Vector3Uniform("Material.Specular", Specular));
   Shader->SetUniform(Vector3Uniform("Material.Emission", Emission));
   Shader->SetUniform(FloatUniform("Material.Shininess", Shininess));
   Shader->SetUniform(Vector4Uniform("Material.Color", Color));

   Shader->SetUniform(IntUniform("Material.DiffuseMap", DiffuseMap->GetUnit()));
   DiffuseMap->Bind();

   Shader->SetUniform(IntUniform("Material.SpecularMap", SpecularMap->GetUnit()));
   SpecularMap->Bind();

   Shader->SetUniform(IntUniform("Material.EmissionMap", EmissionMap->GetUnit()));
   EmissionMap->Bind();
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
