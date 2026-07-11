#pragma once
#include <string>

struct Image {
  Image(const std::string &filePath, bool flip);

  ~Image();

  unsigned char *Data = nullptr;
  int Width = 0;
  int Height = 0;
  int NrChannels = 0;
  bool Flipped;
};