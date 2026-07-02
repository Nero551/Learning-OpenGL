#include "Renderer.h"
#include <GL/gl.h>
#include "Utilities/Services/LoggerService.h"

Material::Material(class Shader shader, Texture texture) : Shader(shader), Texture0(texture) {}

void Material::Use() {
  Shader.Use();

  Shader.SetInt("uTexture0", Texture0.Unit);
  Texture0.Bind();
}