#pragma once

#include <string>
#include "Core/Resource.hpp"

struct Texture : Resource {

   Texture(const std::string &name, int width, int height, unsigned char pixels[]);

   Texture(const std::string &name, const std::string &imagePath);

   unsigned int GetId() const { return Id; }

   void Bind(unsigned int unit);

private:
   void SetParameters();

   unsigned int Id;
};
