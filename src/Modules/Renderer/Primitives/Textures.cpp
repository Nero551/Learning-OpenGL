#include "../Resources/Texture.hpp"
#include "Core/InnerCore/Engine.hpp"
#include "Primitives.hpp"


Texture& Primitives::CreateWhiteTexture() {
    unsigned char white[] = {255, 255, 255, 255};
    auto& whiteTexture = ServiceStore::Ins->Get<ResourceManager>().Load<Texture>("WhiteTexture", 1, 1, white);

    return whiteTexture;
}

Texture& Primitives::CreateBlackTexture() {
    unsigned char black[] = {0, 0, 0, 255};
    auto& blackTexture = ServiceStore::Ins->Get<ResourceManager>().Load<Texture>("BlackTexture", 1, 1, black);
    return blackTexture;
}
