#define STB_IMAGE_IMPLEMENTATION
#include "Renderer.h"
#include <iostream>
#include <string>
#include "../OpenGL.h"
#include "stb_image.h"

Texture::Texture(unsigned int unit, const std::string &imagePath) : Unit(unit) {
  glGenTextures(1, &Id);
  glActiveTexture(GL_TEXTURE0 + Unit);
  glBindTexture(GL_TEXTURE_2D, Id);

  SetParameters();

  int width, height, nrChannels;

  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);

  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed To Load Texture" << "\n";
  }
  stbi_image_free(data);

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