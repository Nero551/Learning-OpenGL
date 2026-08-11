#include "CoordinateAxesScene.hpp"

#include "Core/InnerCore/Engine.hpp"
#include "Core/Services/ResourceManager.hpp"
#include "Modules/Input/Input.hpp"
#include "Modules/Input/Enums/Keys.hpp"
#include "Modules/Renderer/Components/MaterialComponent.hpp"
#include "Modules/Renderer/Components/MeshComponent.hpp"
#include "Modules/Renderer/Primitives/Primitives.hpp"
#include "Utilities/Math/Color.hpp"
#include "World/Novas/Camera.hpp"
#include "World/Novas/Light.hpp"
#include "World/Novas/MeshInstance3D.hpp"
#include "World/Novas/Nova3D.hpp"

namespace E {
static unsigned int lightId = 0;

CoordinateAxesScene::CoordinateAxesScene() {
    auto& resourceManager = Service::Get<ResourceManager>();

    SetRoot(World::Get().CreateEntity<Nova3D>());

    auto& lightShader = resourceManager.Load<Shader>("lightShader");
    lightShader.AssignSource(resourceManager.Load<ShaderSource>("lightFrag", "Assets/Shaders/lightShader.frag",
        ShaderStage::Fragment));
    lightShader.AssignSource(
        resourceManager.Load<ShaderSource>("lightVert", "Assets/Shaders/lightShader.vert", ShaderStage::Vertex));

    auto& lightMaterial = resourceManager.Load<Material>("lightMaterial");
    lightMaterial.Shader = &lightShader;

    auto& light = World::Get().CreateEntity<Light>();
    light.GetComponent<Transform3DComponent>().Rotation.x = Math::Rad(90);
    GetRoot().AttachChild(light);
    lightId = light.Id;

    auto& shader = Service::Get<ResourceManager>().Load<Shader>("AxisShader");
    shader.AssignSource(resourceManager.Load<ShaderSource>("axisFrag", "Assets/Shaders/axisShader.frag",
        ShaderStage::Fragment));
    shader.AssignSource(
        resourceManager.Load<ShaderSource>("axisVert", "Assets/Shaders/axisShader.vert", ShaderStage::Vertex));

    auto& line = Primitives::CreateLine("Line");

    auto& xAxis = World::Get().CreateEntity<MeshInstance3D>();
    xAxis.GetComponent<MeshComponent>().Mesh = &line;
    xAxis.GetComponent<MaterialComponent>().Material = &resourceManager.Load<Material>("X-Axis Material");
    xAxis.GetComponent<MaterialComponent>().Material->Shader = &shader;

    xAxis.GetComponent<Transform3DComponent>().Rotation = {0, Math::Rad(90), 0};
    xAxis.GetComponent<Transform3DComponent>().Position = {-50, 0, 0};
    xAxis.GetComponent<Transform3DComponent>().Scale = {1, 1, 200};
    xAxis.GetComponent<MaterialComponent>().Material->Color = Color::Red;

    GetRoot().AttachChild(xAxis);

    auto& yAxis = World::Get().CreateEntity<MeshInstance3D>();
    yAxis.GetComponent<MeshComponent>().Mesh = &line;
    yAxis.GetComponent<MaterialComponent>().Material = &resourceManager.Load<Material>("Y-Axis Material");
    yAxis.GetComponent<MaterialComponent>().Material->Shader = &shader;

    yAxis.GetComponent<Transform3DComponent>().Rotation = {Math::Rad(-90), 0, 0};
    yAxis.GetComponent<Transform3DComponent>().Position = {0, -50, 0};
    yAxis.GetComponent<Transform3DComponent>().Scale = {1, 1, 200};
    yAxis.GetComponent<MaterialComponent>().Material->Color = Color::Green;

    GetRoot().AttachChild(yAxis);

    auto& zAxis = World::Get().CreateEntity<MeshInstance3D>();
    zAxis.GetComponent<MeshComponent>().Mesh = &line;
    zAxis.GetComponent<MaterialComponent>().Material = &resourceManager.Load<Material>("Z-Axis Material");
    zAxis.GetComponent<MaterialComponent>().Material->Shader = &shader;

    zAxis.GetComponent<Transform3DComponent>().Rotation = {0, 0, 0};
    zAxis.GetComponent<Transform3DComponent>().Position = {0, 0, -50};
    zAxis.GetComponent<Transform3DComponent>().Scale = {1, 1, 200};
    zAxis.GetComponent<MaterialComponent>().Material->Color = Color::Blue;

    GetRoot().AttachChild(zAxis);
}

void CoordinateAxesScene::Update(double dt) {
    auto& light = World::Get().FindEntity(lightId);
    auto& transformComponent = light.GetComponent<Transform3DComponent>();
    auto& input = Engine::Get().GetModule<Input>();

    const auto dtf = static_cast<float>(dt);
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
        transformComponent.Rotation.x += 2.0f * dtf;
    }

    if (input.IsKeyHeld(Key::X)) {
        transformComponent.Rotation.y += 2.0f * dtf;
    }

    if (input.IsKeyHeld(Key::C)) {
        transformComponent.Rotation.z += 2.0f * dtf;
    }
}
}
