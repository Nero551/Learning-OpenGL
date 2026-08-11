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
CoordinateAxesScene::CoordinateAxesScene() {
    auto& resourceManager = Service::Get<ResourceManager>();

    Root = &World::Get().CreateEntity<Nova>();

    auto& lightShader = resourceManager.Load<Shader>("lightShader");
    lightShader.AssignSource(resourceManager.Load<ShaderSource>("lightFrag", "Assets/Shaders/lightShader.frag",
        ShaderStage::Fragment));
    lightShader.AssignSource(
        resourceManager.Load<ShaderSource>("lightVert", "Assets/Shaders/lightShader.vert", ShaderStage::Vertex));

    auto& lightMaterial = resourceManager.Load<Material>("lightMaterial");
    lightMaterial.Shader = &lightShader;

    auto& light = World::Get().CreateEntity<Light>();
    light.GetComponent<Transform3DComponent>().Rotation.x = Math::Rad(32.5);
    light.GetComponent<Transform3DComponent>().Rotation.y = Math::Rad(32.5);
    light.GetComponent<Transform3DComponent>().Rotation.z = Math::Rad(32.5);
    Root->AttachChild(light);

    auto& light2 = World::Get().CreateEntity<Light>();
    light2.GetComponent<Transform3DComponent>().Rotation.x = Math::Rad(-32.5);
    light2.GetComponent<Transform3DComponent>().Rotation.y = Math::Rad(-32.5);
    light2.GetComponent<Transform3DComponent>().Rotation.z = Math::Rad(-32.5);
    Root->AttachChild(light2);

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

    Root->AttachChild(xAxis);

    auto& yAxis = World::Get().CreateEntity<MeshInstance3D>();
    yAxis.GetComponent<MeshComponent>().Mesh = &line;
    yAxis.GetComponent<MaterialComponent>().Material = &resourceManager.Load<Material>("Y-Axis Material");
    yAxis.GetComponent<MaterialComponent>().Material->Shader = &shader;

    yAxis.GetComponent<Transform3DComponent>().Rotation = {Math::Rad(-90), 0, 0};
    yAxis.GetComponent<Transform3DComponent>().Position = {0, -50, 0};
    yAxis.GetComponent<Transform3DComponent>().Scale = {1, 1, 200};
    yAxis.GetComponent<MaterialComponent>().Material->Color = Color::Green;

    Root->AttachChild(yAxis);

    auto& zAxis = World::Get().CreateEntity<MeshInstance3D>();
    zAxis.GetComponent<MeshComponent>().Mesh = &line;
    zAxis.GetComponent<MaterialComponent>().Material = &resourceManager.Load<Material>("Z-Axis Material");
    zAxis.GetComponent<MaterialComponent>().Material->Shader = &shader;

    zAxis.GetComponent<Transform3DComponent>().Rotation = {0, 0, 0};
    zAxis.GetComponent<Transform3DComponent>().Position = {0, 0, -50};
    zAxis.GetComponent<Transform3DComponent>().Scale = {1, 1, 200};
    zAxis.GetComponent<MaterialComponent>().Material->Color = Color::Blue;

    Root->AttachChild(zAxis);
}
}
