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

   Shader->SetUniform(IntUniform("Material.DiffuseMap", 16));
   DiffuseMap->Bind(16);

   Shader->SetUniform(IntUniform("Material.SpecularMap", 15));
   SpecularMap->Bind(15);

   Shader->SetUniform(IntUniform("Material.EmissionMap", 14));
   EmissionMap->Bind(14);
}

void Material::Use() {
   Shader->Use();
   SetProperties();

   for (int slot = 0; slot < MaxTextures; slot++) {
      if (CustomTextures[slot]) {
         Shader->SetUniform(IntUniform(CustomTextures[slot]->Name, slot));
         CustomTextures[slot]->Bind(slot);
      }
   }
}

void Material::AssignTexture(Texture &texture, unsigned int slot) {
   if (slot >= MaxTextures) {
      LoggerService::Error("Texture slot out of bounds: " + texture.Name);
   }
   CustomTextures[slot] = &texture;
}
