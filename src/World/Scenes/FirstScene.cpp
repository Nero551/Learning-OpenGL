#include "FirstScene.hpp"

#include "AssimpScene.hpp"
#include "CoordinateAxesScene.hpp"
#include "../../Modules/Renderer/Primitives/Primitives.hpp"
#include "Core/Services/ResourceManager.hpp"
#include "Modules/Renderer/Uniforms/Vector3Uniform.hpp"
#include "World/Novas/Camera.hpp"
#include "World/Novas/Light.hpp"
#include "World/Novas/MeshInstance3D.hpp"

FirstScene::FirstScene() {
    auto& resourceManager = ServiceStore::Ins->Get<ResourceManager>();
    auto& camera = Engine::Get().World.CreateEntity<Camera>();
    SetActiveCamera(camera);

    SetRoot(Engine::Get().World.CreateEntity<Entity>());

    auto& coordinateAxesScene = Engine::Get().World.CreateScene<CoordinateAxesScene>("Coordinate Axes Scene");
    GetRoot().AttachChild(coordinateAxesScene.GetRoot());

    auto& mesh = Primitives::CreateCube("mesh");
    auto& lightShader = resourceManager.Load<Shader>("lightShader", "Assets/Shaders/lightShader.frag",
        "Assets/Shaders/lightShader.vert");

    auto& lightMaterial = resourceManager.Load<Material>("lightMaterial");
    lightMaterial.Shader = &lightShader;

    auto& light = Engine::Get().World.CreateEntity<Light>();
    light.GetComponent<MaterialComponent>().Material = &lightMaterial;
    light.GetComponent<MeshComponent>().Mesh = &mesh;

    light.GetComponent<Transform3DComponent>().LocalScale = {0.2};
    light.GetComponent<LightComponent>().Ambient = {0.2};
    light.GetComponent<Transform3DComponent>().LocalPosition = {5, 0, 5};
    light.GetComponent<LightComponent>().Type = LightType::Directional;
    GetRoot().AttachChild(light);

    // auto& modelScene = Engine::Get().World.CreateScene<AssimpScene>("barrel", "Assets/Barrel/barrel.obj");
    // GetRoot().AttachChild(modelScene.GetRoot());
    auto& objectShader = resourceManager.Load<Shader>("objectShader", "Assets/Shaders/shader.frag",
        "Assets/Shaders/shader.vert");
    auto& diffuseMap = resourceManager.Load<Texture>("diffuseMap", "Assets/Images/diffuseMap.png");
    auto& specularMap = resourceManager.Load<Texture>("specularMap", "Assets/Images/specularMap.png");

    auto& objectMaterial = resourceManager.Load<Material>("material");
    objectMaterial.Shader = &objectShader;
    objectMaterial.DiffuseMap = &diffuseMap;
    objectMaterial.SpecularMap = &specularMap;

    auto& cube = Engine::Get().World.CreateEntity<MeshInstance3D>();
    cube.GetComponent<MeshComponent>().Mesh = &mesh;
    cube.GetComponent<MaterialComponent>().Material = &objectMaterial;

    GetRoot().AttachChild(cube);
}

void FirstScene::Update(double dt) {}
