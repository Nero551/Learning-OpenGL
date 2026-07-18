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

unsigned int cubeId = 0;

FirstScene::FirstScene() {
    auto& resourceManager = ServiceStore::Ins->Get<ResourceManager>();
    auto& camera = Engine::Get().World.CreateEntity<Camera>();
    SetActiveCamera(camera);

    SetRoot(Engine::Get().World.CreateEntity<Nova3D>());

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
    light.GetComponent<Transform3DComponent>().LocalPosition = {3, 0, 3};
    light.GetComponent<LightComponent>().Type = LightType::Directional;
    GetRoot().AttachChild(light);

    //TODO- extract an abstract class SystemStore/Container, both module and world will inherit/Have
    //TODO- shader preprocessing for custom includes
    //TODO- parent child transform relations
    //TODO- quaternions


    // auto& backpack = Engine::Get().World.CreateScene<AssimpScene>("backpack", "Assets/backpack/backpack.obj");
    // GetRoot().AttachChild(backpack.GetRoot());

    auto& objectShader = resourceManager.Load<Shader>("objectShader", "Assets/Shaders/shader.frag",
        "Assets/Shaders/shader.vert");
    auto& diffuseMap = resourceManager.Load<Texture>("diffuseMap", "Assets/Images/diffuseMap.png");
    auto& specularMap = resourceManager.Load<Texture>("specularMap", "Assets/Images/specularMap.png");

    auto& objectMaterial = resourceManager.Load<Material>("material");
    objectMaterial.Shader = &objectShader;
    objectMaterial.DiffuseMap = &diffuseMap;
    objectMaterial.SpecularMap = &specularMap;
    auto& cube = Engine::Get().World.CreateEntity<MeshInstance3D>();
    cubeId = cube.Id;
    cube.GetComponent<MeshComponent>().Mesh = &mesh;
    cube.GetComponent<MaterialComponent>().Material = &objectMaterial;
    cube.GetComponent<Transform3DComponent>().LocalPosition = {0, 0, 0};
    GetRoot().AttachChild(cube);

    auto& cube2 = Engine::Get().World.CreateEntity<MeshInstance3D>();
    cube2.GetComponent<MeshComponent>().Mesh = &mesh;
    cube2.GetComponent<MaterialComponent>().Material = &objectMaterial;
    cube2.GetComponent<Transform3DComponent>().LocalPosition = {0, 0, 2};
    cube.AttachChild(cube2);
}

void FirstScene::Update(double dt) {
    auto& cube = Engine::Get().World.FindEntity(cubeId);
    auto& transformComponent = cube.GetComponent<Transform3DComponent>();
    auto& input = Engine::Get().GetModule<Input>();

    auto dtf = static_cast<float>(dt);

    if (input.IsKeyHeld(Key::Up)) {
        transformComponent.LocalPosition.z += 2.0f * dtf;
    }
    if (input.IsKeyHeld(Key::Down)) {
        transformComponent.LocalPosition.z -= 2.0f * dtf;
    }
    if (input.IsKeyHeld(Key::Left)) {
        transformComponent.LocalPosition.x -= 2.0f * dtf;
    }
    if (input.IsKeyHeld(Key::Right)) {
        transformComponent.LocalPosition.x += 2.0f * dtf;
    }

    if (input.IsKeyHeld(Key::I)) {
        transformComponent.LocalPosition.y += 2.0f * dtf;
    }
    if (input.IsKeyHeld(Key::O)) {
        transformComponent.LocalPosition.y -= 2.0f * dtf;
    }

    if (input.IsKeyHeld(Key::Z)) {
        transformComponent.LocalEulerRotation.x += 2.0f * dtf;
    }

    if (input.IsKeyHeld(Key::X)) {
        transformComponent.LocalEulerRotation.y += 2.0f * dtf;
    }

    if (input.IsKeyHeld(Key::C)) {
        transformComponent.LocalEulerRotation.z += 2.0f * dtf;
    }
}
