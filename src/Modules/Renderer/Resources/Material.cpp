#include "Material.hpp"

#include "../Uniforms/FloatUniform.hpp"
#include "../Uniforms/IntUniform.hpp"
#include "../Uniforms/Vector3Uniform.hpp"
#include "../Uniforms/Vector4Uniform.hpp"
#include "Utilities/Services/LoggerService.hpp"

Material::Material(const std::string &name) : Resource(name) {}

void Material::Use() {
   Shader->Use();

   Shader->SetUniform(Vector3Uniform("Material.Ambient", Ambient));
   Shader->SetUniform(Vector3Uniform("Material.Diffuse", Diffuse));
   Shader->SetUniform(Vector3Uniform("Material.Specular", Specular));
   Shader->SetUniform(FloatUniform("Material.Shininess", Shininess));
   Shader->SetUniform(Vector4Uniform("Material.Color", MaterialColor));

   for (Texture *texture: Textures) {
      if (texture) {
         Shader->SetUniform(IntUniform(texture->Name, texture->Unit));
         texture->Bind();
      }
   }
}

void Material::AssignShader(struct Shader &shader) { Shader = &shader; }

void Material::AssignTexture(Texture &texture) {
   if (texture.Unit >= Textures.size()) {
      LoggerService::Error("Texture out of bounds: " + texture.Name);
   }

   Textures[texture.Unit] = &texture;
}
