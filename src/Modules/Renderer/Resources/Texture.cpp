#include <OpenGL.hpp>
#include "Texture.hpp"
#include <iostream>
#include <string>
#include "Utilities/Image/Image.hpp"

Texture::Texture(const std::string &name, unsigned int unit, const std::string &imagePath) : Name(name), Unit(unit) {
  glGenTextures(1, &Id);
  glActiveTexture(GL_TEXTURE0 + Unit);
  glBindTexture(GL_TEXTURE_2D, Id);

  SetParameters();

  Image image(imagePath, true);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.Width, image.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.Data);
  glGenerateMipmap(GL_TEXTURE_2D);

  glActiveTexture(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind() {
  glActiveTexture(GL_TEXTURE0 + Unit);
  glBindTexture(GL_TEXTURE_2D, Id);
}

void Texture::SetParameters() {
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}