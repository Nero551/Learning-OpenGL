#include "../Resources/Texture.hpp"
#include "Core/Engine.hpp"
#include "Primitives.hpp"


Texture &Primitives::CreateWhiteTexture() {
   unsigned char white[] = {255, 255, 255, 255};
   auto &whiteTexture = Engine::Ins->ResourceManager.Load<Texture>("WhiteTexture", 15, 1, 1, white);

   return whiteTexture;
}

Texture &Primitives::CreateBlackTexture() {
   unsigned char black[] = {0, 0, 0, 255};
   auto &blackTexture = Engine::Ins->ResourceManager.Load<Texture>("BlackTexture", 14, 1, 1, black);

   return blackTexture;
}
