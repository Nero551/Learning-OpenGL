#include "../Resources/Texture.hpp"
#include "Core/Services/ResourceManager.hpp"
#include "Primitives.hpp"

namespace E {
Texture& Primitives::CreateWhiteTexture() {
    unsigned char white[] = { 255, 255, 255, 255 };
    auto& whiteTexture = Service::Get<ResourceManager>().Load<Texture>("WhiteTexture", 1, 1, white);

    return whiteTexture;
}

Texture& Primitives::CreateBlackTexture() {
    unsigned char black[] = { 0, 0, 0, 255 };
    auto& blackTexture = Service::Get<ResourceManager>().Load<Texture>("BlackTexture", 1, 1, black);
    return blackTexture;
}
} // namespace E
