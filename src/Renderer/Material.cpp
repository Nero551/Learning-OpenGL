#include "Renderer.h"

Material::Material(class Shader &shader) : Shader(shader) {}

void Material::Use() {    
  Shader.Use();

  if (Texture0) {
    Shader.SetInt("Texture0", Texture0->Unit);
    Texture0->Bind();
  }

  if (Texture1) {
    Shader.SetInt("Texture1", Texture1->Unit);
    Texture1->Bind();
  }

  if (Texture2) {
    Shader.SetInt("Texture2", Texture2->Unit);
    Texture2->Bind();
  }
}