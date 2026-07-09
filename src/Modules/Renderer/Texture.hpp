#pragma once

#include <string>

class Texture {
public:
  std::string Name;
  unsigned int Id;
  unsigned int Unit;
  Texture(const std::string &name, unsigned int unit, const std::string &imagePath);

  void Bind();

private:
  void SetParameters();
};