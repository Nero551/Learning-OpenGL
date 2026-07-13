#pragma once

#include <string>
#include "Core/Resource.hpp"

struct Texture : Resource {

   Texture(const std::string &name, unsigned int unit, int width, int height, unsigned char pixels[]);

   Texture(const std::string &name, unsigned int unit, const std::string &imagePath);

   unsigned int GetId() const { return Id; }
   unsigned int GetUnit() const { return Unit; }

   void Bind();

private:
   void SetParameters();

   unsigned int Id;
   unsigned int Unit;
};
