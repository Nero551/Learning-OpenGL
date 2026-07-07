#pragma once
#include <string>

struct Image {
  Image(const std::string &filePath);
  ~Image();
  unsigned char *Data = nullptr;
  int Width = 0;
  int Height = 0;
  int NrChannels = 0;
};