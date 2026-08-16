#include "FirstScene.hpp"

#include "../../Modules/Renderer/Primitives/Primitives.hpp"
#include "AssimpScene.hpp"
#include "Core/Services/ResourceManager.hpp"
#include "Modules/Renderer/Uniforms/Vector3Uniform.hpp"
#include "World/Novas/Light.hpp"
#include "World/Novas/MeshInstance3D.hpp"

namespace E {
FirstScene::FirstScene() {
    auto& resourceManager = Service::Get<ResourceManager>();
    Root = &World::Get().CreateEntity<Nova3D>();

    auto& mesh = Primitives::CreateCube("mesh");

    auto& lightShader = resourceManager.Load<Shader>("lightShader");
    lightShader.AssignSource(
        resourceManager.Load<ShaderSource>("lightFrag", "Assets/Shaders/lightShader.frag", ShaderStage::Fragment));
    lightShader.AssignSource(
        resourceManager.Load<ShaderSource>("lightVert", "Assets/Shaders/lightShader.vert", ShaderStage::Vertex));

    auto& lightMaterial = resourceManager.Load<Material>("lightMaterial");
    lightMaterial.Shader = &lightShader;

    auto& light = World::Get().CreateEntity<Light>();

    light.GetComponent<Transform3DComponent>().Scale = M::Vector3(0.2);
    light.GetComponent<LightComponent>().Ambient = {0.2};
    light.GetComponent<LightComponent>().Diffuse = {0.2};
    light.GetComponent<Transform3DComponent>().Position = {0, 0, 0};
    light.GetComponent<LightComponent>().Type = LightType::Directional;
    Root->AttachChild(light);

    // TODO- quaternions

    auto& objectShader = resourceManager.Load<Shader>("objectShader");
    objectShader.AssignSource(
        resourceManager.Load<ShaderSource>("objectFrag", "Assets/Shaders/shader.frag", ShaderStage::Fragment));
    objectShader.AssignSource(
        resourceManager.Load<ShaderSource>("objectVert", "Assets/Shaders/shader.vert", ShaderStage::Vertex));

    objectShader.HotReload = true;

    auto& objectMaterial = resourceManager.Load<Material>("material");
    objectMaterial.Shader = &objectShader;

    auto& cube = World::Get().CreateEntity<MeshInstance3D>();
    cube.GetComponent<MeshComponent>().Mesh = &mesh;
    cube.GetComponent<MaterialComponent>().Material = &objectMaterial;
    cube.GetComponent<Transform3DComponent>().Position = {0, 0, 0};
    Root->AttachChild(cube);
}
} // namespace E
