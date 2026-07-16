#include "FirstScene.hpp"

#include "AssimpScene.hpp"
#include "CoordinateAxesScene.hpp"
#include "Modules/Input/Input.hpp"
#include "Modules/Input/Enums/Keys.hpp"
#include "../../Modules/Renderer/Primitives/Primitives.hpp"
#include "Core/Services/ResourceManager.hpp"
#include "Modules/Renderer/Uniforms/Vector3Uniform.hpp"
#include "World/Novas/Camera.hpp"
#include "World/Novas/Light.hpp"
#include "World/Novas/MeshInstance3D.hpp"

FirstScene::FirstScene() {
    auto& resourceManager = ServiceStore::Ins->Get<ResourceManager>();
    auto& camera = Engine::Ins->World.CreateEntity<Camera>();
    camera.GetComponent<CameraComponent>().AspectRatio = Engine::Ins->Window.Width / Engine::Ins->Window.Height;
    SetActiveCamera(camera);

    SetRoot(Engine::Ins->World.CreateEntity<Entity>());

    auto& coordinateAxesScene = Engine::Ins->World.CreateScene<CoordinateAxesScene>("Coordinate Axes Scene");
    GetRoot().AttachChild(coordinateAxesScene.GetRoot());

    auto& mesh = Primitives::CreateCube("mesh");

    auto& lightShader = resourceManager.Load<Shader>("lightShader", "Assets/Shaders/lightShader.frag",
        "Assets/Shaders/lightShader.vert");

    auto& lightMaterial = resourceManager.Load<Material>("lightMaterial");
    lightMaterial.Shader = &lightShader;

    auto& light2 = Engine::Ins->World.CreateEntity<Light>();
    light2.GetComponent<MaterialComponent>().Material = &lightMaterial;
    light2.GetComponent<MeshComponent>().Mesh = &mesh;

    light2.GetComponent<Transform3DComponent>().LocalScale = {0.2};

    light2.GetComponent<LightComponent>().Ambient = {0.2};
    light2.GetComponent<LightComponent>().Type = LightType::Directional;
    GetRoot().AttachChild(light2);

    // Engine::Ins->World.CreateScene<AssimpScene>("Assets");
}

void FirstScene::Update(double dt) {}
