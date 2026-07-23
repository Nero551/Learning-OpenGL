#include "FirstScene.hpp"

#include "AssimpScene.hpp"
#include "CoordinateAxesScene.hpp"
#include "../../Modules/Renderer/Primitives/Primitives.hpp"
#include "Core/Services/ResourceManager.hpp"
#include "Modules/Input/Input.hpp"
#include "Modules/Input/Enums/Keys.hpp"
#include "Modules/Renderer/Uniforms/Vector3Uniform.hpp"
#include "World/Novas/Camera.hpp"
#include "World/Novas/Light.hpp"
#include "World/Novas/MeshInstance3D.hpp"

static unsigned int cubeId = 0;

FirstScene::FirstScene() {
    auto& resourceManager = ServiceStore::Ins->Get<ResourceManager>();
    auto& camera = Engine::Get().World.CreateEntity<Camera>();
    SetActiveCamera(camera);

    SetRoot(Engine::Get().World.CreateEntity<Nova3D>());

    auto& coordinateAxesScene = Engine::Get().World.CreateScene<CoordinateAxesScene>("Coordinate Axes Scene");
    GetRoot().AttachChild(coordinateAxesScene.GetRoot());

    auto& mesh = Primitives::CreateCube("mesh");

    auto& lightShader = resourceManager.Load<Shader>("lightShader");
    lightShader.AssignSource(resourceManager.Load<ShaderSource>("lightFrag", "Assets/Shaders/lightShader.frag",
        ShaderStage::Fragment));
    lightShader.AssignSource(
        resourceManager.Load<ShaderSource>("lightVert", "Assets/Shaders/shader.vert", ShaderStage::Vertex));

    auto& lightMaterial = resourceManager.Load<Material>("lightMaterial");
    lightMaterial.Shader = &lightShader;

    auto& light = Engine::Get().World.CreateEntity<Light>();
    light.GetComponent<MaterialComponent>().Material = &lightMaterial;
    light.GetComponent<MeshComponent>().Mesh = &mesh;

    light.GetComponent<Transform3DComponent>().LocalScale = Vector3(0.2);
    light.GetComponent<LightComponent>().Ambient = {0.2};
    light.GetComponent<Transform3DComponent>().LocalPosition = {3, 0, 3};
    light.GetComponent<LightComponent>().Type = LightType::Directional;
    GetRoot().AttachChild(light);

    //TODO- quaternions

    auto& objectShader = resourceManager.Load<Shader>("objectShader");
    objectShader.AssignSource(
        resourceManager.Load<ShaderSource>("objectFrag", "Assets/Shaders/shader.frag", ShaderStage::Fragment));
    objectShader.AssignSource(
        resourceManager.Load<ShaderSource>("objectVert", "Assets/Shaders/shader.vert", ShaderStage::Vertex));

    auto& diffuseMap = resourceManager.Load<Texture>("diffuseMap", "Assets/Images/diffuseMap.png");
    auto& specularMap = resourceManager.Load<Texture>("specularMap", "Assets/Images/specularMap.png");

    auto& objectMaterial = resourceManager.Load<Material>("material");
    objectMaterial.Shader = &objectShader;
    objectMaterial.DiffuseMap = &diffuseMap;
    objectMaterial.SpecularMap = &specularMap;

    auto& cube = Engine::Get().World.CreateEntity<MeshInstance3D>();
    cube.GetComponent<MeshComponent>().Mesh = &mesh;
    cube.GetComponent<MaterialComponent>().Material = &objectMaterial;
    cube.GetComponent<Transform3DComponent>().LocalPosition = {0, 0, 3};
    GetRoot().AttachChild(cube);
    cubeId = cube.Id;
}


void FirstScene::FixedUpdate(double fdt) {
    auto& cube = Engine::Get().World.FindEntity(cubeId);
    auto& transformComponent = cube.GetComponent<Transform3DComponent>();
    auto& input = Engine::Get().GetModule<Input>();


    cube.GetComponent<MaterialComponent>().Material->Shader->Reload();

    const auto fdtf = static_cast<float>(fdt);
    if (input.IsKeyHeld(Key::Up)) {
        transformComponent.LocalPosition->z += 2.0f * fdtf;
    }
    if (input.IsKeyHeld(Key::Down)) {
        transformComponent.LocalPosition->z -= 2.0f * fdtf;
    }
    if (input.IsKeyHeld(Key::Left)) {
        transformComponent.LocalPosition->x -= 2.0f * fdtf;
    }
    if (input.IsKeyHeld(Key::Right)) {
        transformComponent.LocalPosition->x += 2.0f * fdtf;
    }

    if (input.IsKeyHeld(Key::I)) {
        transformComponent.LocalPosition->y += 2.0f * fdtf;
    }
    if (input.IsKeyHeld(Key::O)) {
        transformComponent.LocalPosition->y -= 2.0f * fdtf;
    }

    if (input.IsKeyHeld(Key::Z)) {
        transformComponent.LocalEulerRotation->x += 2.0f * fdtf;
    }

    if (input.IsKeyHeld(Key::X)) {
        transformComponent.LocalEulerRotation->y += 2.0f * fdtf;
    }

    if (input.IsKeyHeld(Key::C)) {
        transformComponent.LocalEulerRotation->z += 2.0f * fdtf;
    }
}
