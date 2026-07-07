#pragma once

#include <string>

class Texture {
public:
  unsigned int Id;
  unsigned int Unit;
  Texture(unsigned int unit, const std::string &imagePath);

  void Bind();

private:
  void SetParameters();
};