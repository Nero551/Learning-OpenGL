#define STB_IMAGE_IMPLEMENTATION
#include "Image.hpp"
#include <string>
#include <stb_image.h>
#include "Utilities/Services/LoggerService.hpp"

Image::Image(const std::string &filePath, bool flip) {
  stbi_set_flip_vertically_on_load(flip);
  Flipped = flip;
  Data = stbi_load(filePath.c_str(), &Width, &Height, &NrChannels, 0);

  if (!Data) {
    LoggerService::Error("Failed To Load Image: " + filePath);
  }
}

Image::~Image() { stbi_image_free(Data); }