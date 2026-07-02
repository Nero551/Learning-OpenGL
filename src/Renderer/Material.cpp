#include "Renderer.h"
#include <GL/gl.h>
#include "../Services/LoggerService.h"

Material::Material(class Shader &shader) : Shader(shader) {}

void Material::Use() {
  Shader.Use();
  

  if (Texture0) {
    Shader.SetInt("uTexture0", Texture0->Unit);
    Texture0->Bind();
  }

  if (Texture1) {
    Shader.SetInt("uTexture1", Texture1->Unit);
    Texture1->Bind();
  }

  if (Texture2) {
    Shader.SetInt("uTexture2", Texture2->Unit);
    Texture2->Bind();
  }

  
}