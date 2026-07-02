#define STB_IMAGE_IMPLEMENTATION
#include "Image.h"
#include <string>
#include <stb_image.h>
#include "Utilities/Services/LoggerService.h"

Image::Image(const std::string &filePath) {
  stbi_set_flip_vertically_on_load(true);
  Data = stbi_load(filePath.c_str(), &Width, &Height, &NrChannels, 0);

  if (!Data) {
    LoggerService::Error("Failed To Load Image: " + filePath);
  }
}

Image::~Image() { stbi_image_free(Data); }