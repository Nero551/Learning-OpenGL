#include "AssimpScene.hpp"
#include<assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Core/InnerCore/Engine.hpp"
#include "Core/Services/ResourceManager.hpp"
#include "World/Novas/MeshInstance3D.hpp"

Assimp::Importer importer;

void AssimpScene::ProcessNode(aiNode* node, const aiScene* scene) {
    auto& resourceManager = ServiceStore::Ins->Get<ResourceManager>();
    //PROCESSING...
    //TODO- continue Assimp
    auto& entity = Engine::Get().World.CreateEntity<Entity>();
    entity.AddComponent<Transform3DComponent>();
    GetRoot().AttachChild(entity);

    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        auto& meshComponent = entity.AddComponent<MeshComponent>();
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        for (unsigned int v = 0; i < mesh->mNumVertices; i++) {}
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene);
    }
}

AssimpScene::AssimpScene(const std::string& filepath) {
    SetRoot(Engine::Get().World.CreateEntity<Entity>());

    //TODO- cuz of hyprland , the aspect ratio is incorrect cuz it uses windoww tiling manager , FIX

    const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        Logger::Error("ASSIMP FAILED TO LOAD SCENE: ", importer.GetErrorString());
        return;
    }

    std::string directory = filepath.substr(0, filepath.find_last_of('/'));
    ProcessNode(scene->mRootNode, scene);
}

void AssimpScene::Update(double dt) {}
