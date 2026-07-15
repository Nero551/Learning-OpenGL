#include "CoordinateAxesScene.hpp"

#include "Core/InnerCore/Engine.hpp"
#include "Modules/Renderer/Components/MaterialComponent.hpp"
#include "Modules/Renderer/Components/MeshComponent.hpp"
#include "Modules/Renderer/Primitives/Primitives.hpp"
#include "Utilities/Math/Color.hpp"
#include "World/Entities/Axis.hpp"

void CoordinateAxesScene::Initialize() {
    auto& resourceManager = ServiceStore::Ins->GetService<ResourceManager>();

    auto& shader = ServiceStore::Ins->GetService<ResourceManager>().Load<Shader>("AxisShader",
        "Assets/Shaders/axisShader.frag",
        "Assets/Shaders/axisShader.vert");
    auto& line = Primitives::CreateLine("Line");

    auto& xAxis = CreateEntity<Axis>();
    xAxis.GetComponent<MeshComponent>().Mesh = &line;
    xAxis.GetComponent<MaterialComponent>().Material = &resourceManager.Load<Material>("X-Axis Material");
    xAxis.GetComponent<MaterialComponent>().Material->Shader = &shader;

    xAxis.GetComponent<TransformComponent>().EulerRotation = {0, Math::Radians(90), 0};
    xAxis.GetComponent<TransformComponent>().Position = {-50, 0, 0};
    xAxis.GetComponent<TransformComponent>().Scale = {1, 1, 200};
    xAxis.GetComponent<MaterialComponent>().Material->Color = Color::Red;

    auto& yAxis = CreateEntity<Axis>();
    yAxis.GetComponent<MeshComponent>().Mesh = &line;
    yAxis.GetComponent<MaterialComponent>().Material = &resourceManager.Load<Material>("Y-Axis Material");;
    yAxis.GetComponent<MaterialComponent>().Material->Shader = &shader;

    yAxis.GetComponent<TransformComponent>().EulerRotation = {Math::Radians(-90), 0, 0};
    yAxis.GetComponent<TransformComponent>().Position = {0, -50, 0};
    yAxis.GetComponent<TransformComponent>().Scale = {1, 1, 200};
    yAxis.GetComponent<MaterialComponent>().Material->Color = Color::Green;

    auto& zAxis = CreateEntity<Axis>();
    zAxis.GetComponent<MeshComponent>().Mesh = &line;
    zAxis.GetComponent<MaterialComponent>().Material = &resourceManager.Load<Material>("Z-Axis Material");
    zAxis.GetComponent<MaterialComponent>().Material->Shader = &shader;

    zAxis.GetComponent<TransformComponent>().EulerRotation = {0, 0, 0};
    zAxis.GetComponent<TransformComponent>().Position = {0, 0, -50};
    zAxis.GetComponent<TransformComponent>().Scale = {1, 1, 200};
    zAxis.GetComponent<MaterialComponent>().Material->Color = Color::Blue;
}

void CoordinateAxesScene::Update(double dt) {}
