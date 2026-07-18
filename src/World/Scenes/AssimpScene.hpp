#pragma once

#include <assimp/scene.h>

#include "Core/OuterCore/Scene.hpp"
#include "Modules/Renderer/Resources/Mesh.hpp"

struct AssimpScene : Scene {
    AssimpScene(const std::string& filepath);

    void Update(double dt) override;

private:
    void ProcessNode(aiNode* node, const aiScene* scene, const std::string& directory);
};
