module;

export module Material;

import Shader;
import Texture;

export struct Material {
public:
  Shader shader;
  Texture Texture0;

  Material(Shader shader, Texture texture) : shader(shader), Texture0(texture) {}

  void Use() {
    shader.Use();

    shader.SetInt("uTexture0", Texture0.Unit);
    Texture0.Bind();
  }
};
