#pragma once
#include "../Resources/Mesh.hpp"
#include "../Resources/Texture.hpp"

namespace Primitives {
   Mesh &CreateCube(const std::string &name);

   Texture &CreateWhiteTexture();

   Texture &CreateBlackTexture();
}
