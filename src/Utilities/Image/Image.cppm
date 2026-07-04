module;

#define STB_IMAGE_IMPLEMENTATION
#include <string>
#include <stb_image.h>

export module Image;

import LoggerService;


export struct Image {
  Image(const std::string &filePath) {
    stbi_set_flip_vertically_on_load(true);
    Data = stbi_load(filePath.c_str(), &Width, &Height, &NrChannels, 0);

    if (!Data) {
      LoggerService::Error("Failed To Load Image: " + filePath);
    }
  }
  ~Image() { stbi_image_free(Data); }
  unsigned char *Data = nullptr;
  int Width = 0;
  int Height = 0;
  int NrChannels = 0;

  Image(const Image &) = delete;
  Image &operator=(const Image &) = delete;

  Image(Image &&) noexcept;
  Image &operator=(Image &&) noexcept;
};