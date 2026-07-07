#include "Renderer.hpp"
#include <OpenGL.hpp>
#include "Utilities/Services/LoggerService.hpp"

Material::Material(class Shader shader, Texture texture) : Shader(shader), Texture0(texture) {}

void Material::Use() {
  Shader.Use();

  Shader.SetInt("uTexture0", Texture0.Unit);
  Texture0.Bind();

}