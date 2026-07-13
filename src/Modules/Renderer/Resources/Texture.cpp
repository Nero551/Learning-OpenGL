#include <OpenGL.hpp>
#include "Texture.hpp"
#include <iostream>
#include <string>
#include "Utilities/Image/Image.hpp"
#include "Utilities/Services/LoggerService.hpp"

Texture::Texture(const std::string &name, unsigned int unit, int width, int height, unsigned char pixels[]) :
   Resource(name), Unit(unit) {
   glGenTextures(1, &Id);
   glActiveTexture(GL_TEXTURE0 + Unit);
   glBindTexture(GL_TEXTURE_2D, Id);

   SetParameters();

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
   glGenerateMipmap(GL_TEXTURE_2D);

   glActiveTexture(0);
   glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const std::string &name, unsigned int unit, const std::string &imagePath) :
   Resource(name), Unit(unit) {
   glGenTextures(1, &Id);
   glActiveTexture(GL_TEXTURE0 + Unit);
   glBindTexture(GL_TEXTURE_2D, Id);

   SetParameters();

   Image image(imagePath, true);

   GLenum format = GL_RED;

   switch (image.NrChannels) {
      case 1: format = GL_RED;
         break;
      case 3: format = GL_RGB;
         break;
      case 4: format = GL_RGBA;
         break;
      default: LoggerService::Error("Unsupported Texture Channel Count");
   }

   glTexImage2D(GL_TEXTURE_2D, 0, format, image.Width, image.Height, 0, format, GL_UNSIGNED_BYTE, image.Data);
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
