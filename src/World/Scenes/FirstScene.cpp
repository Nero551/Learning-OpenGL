#include "FirstScene.hpp"

#include "CoordinateAxesScene.hpp"
#include "Modules/Input/Input.hpp"
#include "Modules/Input/Enums/Keys.hpp"
#include "../../Modules/Renderer/Primitives/Primitives.hpp"
#include "Modules/Renderer/Uniforms/Vector3Uniform.hpp"
#include "World/Novas/Camera.hpp"
#include "World/Novas/Light.hpp"
#include "World/Novas/MeshInstance3D.hpp"

unsigned int lightId;

void FirstScene::Initialize() {
    auto& resourceManager = ServiceStore::Ins->Get<ResourceManager>();
    auto& camera = Engine::Ins->World.CreateEntity<Camera>();
    camera.GetComponent<CameraComponent>().AspectRatio = Engine::Ins->Window.Width / Engine::Ins->Window.Height;
    SetActiveCamera(camera);

    SetRoot(Engine::Ins->World.CreateEntity<Entity>());

    auto& coordinateAxesScene = Engine::Ins->World.CreateScene<CoordinateAxesScene>("Coordinate Axes Scene");
    GetRoot().AddChild(coordinateAxesScene.GetRoot());

    auto& mesh = Primitives::CreateCube("mesh");

    auto& objectShader = resourceManager.Load<Shader>("shader", "Assets/Shaders/shader.frag",
        "Assets/Shaders/shader.vert");

    auto& diffuseMap = resourceManager.Load<Texture>("diffuseMap", "Assets/Images/diffuseMap.png");
    auto& specularMap = resourceManager.Load<Texture>("specularMap", "Assets/Images/specularMap.png");
    auto& objectMaterial = resourceManager.Load<Material>("material");
    objectMaterial.Shader = &objectShader;
    objectMaterial.DiffuseMap = &diffuseMap;
    objectMaterial.SpecularMap = &specularMap;

    //TODO- make the Nova hierarchy

    for (float i = 0; i < 6; i += 0.5) {
        auto& cube = Engine::Ins->World.CreateEntity<MeshInstance3D>();
        cube.GetComponent<MaterialComponent>().Material = &objectMaterial;
        cube.GetComponent<MeshComponent>().Mesh = &mesh;
        cube.GetComponent<Transform3DComponent>().Position = {std::cos(i) * 5, 0, std::sin(i) * 5};
        GetRoot().AddChild(cube);
    }

    auto& cube = Engine::Ins->World.CreateEntity<MeshInstance3D>();
    cube.GetComponent<MaterialComponent>().Material = &objectMaterial;
    cube.GetComponent<MeshComponent>().Mesh = &mesh;
    cube.GetComponent<Transform3DComponent>().Position = {0, 0, 1};
    GetRoot().AddChild(cube);

    auto& lightShader = resourceManager.Load<Shader>("lightShader", "Assets/Shaders/lightShader.frag",
        "Assets/Shaders/lightShader.vert");

    auto& lightMaterial = resourceManager.Load<Material>("lightMaterial");
    lightMaterial.Shader = &lightShader;

    auto& light = Engine::Ins->World.CreateEntity<Light>();
    light.GetComponent<MaterialComponent>().Material = &lightMaterial;
    light.GetComponent<MeshComponent>().Mesh = &mesh;

    light.GetComponent<Transform3DComponent>().Scale = {0.2};

    light.GetComponent<LightComponent>().Type = LightType::Spot;

    GetRoot().AddChild(light);

    lightId = light.Id; //Temporary

    auto& light2 = Engine::Ins->World.CreateEntity<Light>();
    light2.GetComponent<MaterialComponent>().Material = &lightMaterial;
    light2.GetComponent<MeshComponent>().Mesh = &mesh;

    light2.GetComponent<Transform3DComponent>().Scale = {0.2};

    light2.GetComponent<LightComponent>().Type = LightType::Directional;
    GetRoot().AddChild(light2);
}

void FirstScene::Update(double dt) {
    auto& light = Engine::Ins->World.FindEntity(lightId);
    auto& transformComponent = light.GetComponent<Transform3DComponent>();
    auto& input = Engine::Ins->GetModule<Input>();

    auto dtf = static_cast<float>(dt);

    if (input.IsKeyHeld(Key::Up)) {
        transformComponent.Position.z += 2.0f * dtf;
    }
    if (input.IsKeyHeld(Key::Down)) {
        transformComponent.Position.z -= 2.0f * dtf;
    }
    if (input.IsKeyHeld(Key::Left)) {
        transformComponent.Position.x -= 2.0f * dtf;
    }
    if (input.IsKeyHeld(Key::Right)) {
        transformComponent.Position.x += 2.0f * dtf;
    }

    if (input.IsKeyHeld(Key::I)) {
        transformComponent.Position.y += 2.0f * dtf;
    }
    if (input.IsKeyHeld(Key::O)) {
        transformComponent.Position.y -= 2.0f * dtf;
    }

    if (input.IsKeyHeld(Key::Z)) {
        transformComponent.EulerRotation.x += 2.0f * dtf;
    }

    if (input.IsKeyHeld(Key::X)) {
        transformComponent.EulerRotation.y += 2.0f * dtf;
    }

    if (input.IsKeyHeld(Key::C)) {
        transformComponent.EulerRotation.z += 2.0f * dtf;
    }
}
