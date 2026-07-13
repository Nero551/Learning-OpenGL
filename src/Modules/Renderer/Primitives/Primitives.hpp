#pragma once
#include "../Resources/Mesh.hpp"
#include "../Resources/Texture.hpp"

namespace Primitives {
   Mesh &CreateCube(const std::string &name);

   Mesh &CreateUVSphere(const std::string &name, float radius = 0.5, int sectors = 32, int stacks = 16);

   Mesh &CreateQuad(const std::string &name);

   Texture &CreateWhiteTexture();

   Texture &CreateBlackTexture();
}
