#include "AssimpScene.hpp"

#include<assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Core/InnerCore/Engine.hpp"
#include "Core/Services/ResourceManager.hpp"
#include "World/Novas/MeshInstance3D.hpp"

Assimp::Importer importer;

void ProcessVertices(std::vector<Vertex>& vertices, const aiMesh* mesh) {
    for (unsigned int v = 0; v < mesh->mNumVertices; v++) {
        Vector4 pos = {mesh->mVertices[v].x, mesh->mVertices[v].y, mesh->mVertices[v].z, 1};
        Vector3 normal = {mesh->mNormals[v].x, mesh->mNormals[v].y, mesh->mNormals[v].z};
        Vector2 uv;
        if (mesh->mTextureCoords[0]) {
            uv = {mesh->mTextureCoords[0][v].x, mesh->mTextureCoords[0][v].y};
        }
        else {
            uv = {0.0f, 0.0f};
        }
        vertices.emplace_back(pos, Vector4(1), uv, normal);
    }
}

void ProcessFaces(std::vector<unsigned int>& indices, const aiMesh* mesh) {
    for (unsigned int f = 0; f < mesh->mNumFaces; f++) {
        aiFace face = mesh->mFaces[f];
        for (unsigned int i = 0; i < face.mNumIndices; i++) {
            indices.push_back(face.mIndices[i]);
        }
    }
}

Material& ProcessMaterial(const aiScene* scene, const aiMesh* mesh, const std::string& directory) {
    auto& resourceManager = ServiceStore::Ins->Get<ResourceManager>();
    //Material
    auto& material = resourceManager.Load<Material>("material_" + std::to_string(mesh->mMaterialIndex));
    material.Shader = &resourceManager.Load<Shader>("s");
    material.Shader->AssignSource(
        resourceManager.Load<ShaderSource>("s", "Assets/Shaders/shader.frag", ShaderStage::Fragment));
    material.Shader->AssignSource(
        resourceManager.Load<ShaderSource>("s", "Assets/Shaders/shader.vert", ShaderStage::Vertex));

    aiMaterial* aiMat = scene->mMaterials[mesh->mMaterialIndex];

    //Diffuse maps
    for (unsigned int t = 0; t < aiMat->GetTextureCount(aiTextureType_DIFFUSE); t++) {
        aiString str;
        aiMat->GetTexture(aiTextureType_DIFFUSE, t, &str);
        auto& diffuseMap = resourceManager.Load<Texture>("diffuse" + std::to_string(t),
            std::filesystem::path(directory) / str.C_Str());
        material.DiffuseMap = &diffuseMap;
    }

    //Specular maps
    for (unsigned int t = 0; t < aiMat->GetTextureCount(aiTextureType_SPECULAR); t++) {
        aiString str;
        aiMat->GetTexture(aiTextureType_SPECULAR, t, &str);
        auto& specularMap = resourceManager.Load<Texture>("specular" + std::to_string(t),
            std::filesystem::path(directory) / str.C_Str());
        material.SpecularMap = &specularMap;
    }
    return material;
}

void ProcessNode(const aiNode* node, const aiScene* scene, const std::string& directory, Entity& parent) {
    auto& resourceManager = ServiceStore::Ins->Get<ResourceManager>();
    auto& entity = Engine::Get().World.CreateEntity<Nova3D>();

    //Mesh
    for (unsigned int m = 0; m < node->mNumMeshes; m++) {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        aiMesh* mesh = scene->mMeshes[node->mMeshes[m]];

        ProcessVertices(vertices, mesh);
        ProcessFaces(indices, mesh);
        auto& material = ProcessMaterial(scene, mesh, directory);

        entity.AddComponent<MeshComponent>().Mesh = &resourceManager.Load<Mesh>(
            "mesh_" + std::to_string(node->mMeshes[m]), vertices, indices);

        entity.AddComponent<MaterialComponent>().Material = &material;
    }

    parent.AttachChild(entity);

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene, directory, entity);
    }
}

AssimpScene::AssimpScene(const std::string& filepath) {
    SetRoot(Engine::Get().World.CreateEntity<Nova3D>());

    const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        Logger::Error("[ASSIMP] Failed To Load Scene: ", importer.GetErrorString());
        return;
    }

    std::string directory = filepath.substr(0, filepath.find_last_of('/'));
    ProcessNode(scene->mRootNode, scene, directory, GetRoot());
}

void AssimpScene::Update(double dt) {}
