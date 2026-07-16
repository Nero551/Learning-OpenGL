#include "CoordinateAxesScene.hpp"

#include "Core/InnerCore/Engine.hpp"
#include "Modules/Renderer/Components/MaterialComponent.hpp"
#include "Modules/Renderer/Components/MeshComponent.hpp"
#include "Modules/Renderer/Primitives/Primitives.hpp"
#include "Utilities/Math/Color.hpp"
#include "World/Entities/Axis.hpp"

void CoordinateAxesScene::Initialize() {
    auto& resourceManager = ServiceStore::Ins->Get<ResourceManager>();

    SetRoot(Engine::Ins->World.CreateEntity<Entity>());

    auto& shader = ServiceStore::Ins->Get<ResourceManager>().Load<Shader>("AxisShader",
        "Assets/Shaders/axisShader.frag",
        "Assets/Shaders/axisShader.vert");
    auto& line = Primitives::CreateLine("Line");

    auto& xAxis = Engine::Ins->World.CreateEntity<Axis>();
    xAxis.GetComponent<MeshComponent>().Mesh = &line;
    xAxis.GetComponent<MaterialComponent>().Material = &resourceManager.Load<Material>("X-Axis Material");
    xAxis.GetComponent<MaterialComponent>().Material->Shader = &shader;

    xAxis.GetComponent<Transform3DComponent>().EulerRotation = {0, Math::Radians(90), 0};
    xAxis.GetComponent<Transform3DComponent>().Position = {-50, 0, 0};
    xAxis.GetComponent<Transform3DComponent>().Scale = {1, 1, 200};
    xAxis.GetComponent<MaterialComponent>().Material->Color = Color::Red;

    GetRoot().AddChild(xAxis);

    auto& yAxis = Engine::Ins->World.CreateEntity<Axis>();
    yAxis.GetComponent<MeshComponent>().Mesh = &line;
    yAxis.GetComponent<MaterialComponent>().Material = &resourceManager.Load<Material>("Y-Axis Material");;
    yAxis.GetComponent<MaterialComponent>().Material->Shader = &shader;

    yAxis.GetComponent<Transform3DComponent>().EulerRotation = {Math::Radians(-90), 0, 0};
    yAxis.GetComponent<Transform3DComponent>().Position = {0, -50, 0};
    yAxis.GetComponent<Transform3DComponent>().Scale = {1, 1, 200};
    yAxis.GetComponent<MaterialComponent>().Material->Color = Color::Green;

    GetRoot().AddChild(yAxis);

    auto& zAxis = Engine::Ins->World.CreateEntity<Axis>();
    zAxis.GetComponent<MeshComponent>().Mesh = &line;
    zAxis.GetComponent<MaterialComponent>().Material = &resourceManager.Load<Material>("Z-Axis Material");
    zAxis.GetComponent<MaterialComponent>().Material->Shader = &shader;

    zAxis.GetComponent<Transform3DComponent>().EulerRotation = {0, 0, 0};
    zAxis.GetComponent<Transform3DComponent>().Position = {0, 0, -50};
    zAxis.GetComponent<Transform3DComponent>().Scale = {1, 1, 200};
    zAxis.GetComponent<MaterialComponent>().Material->Color = Color::Blue;

    GetRoot().AddChild(zAxis);
}

void CoordinateAxesScene::Update(double dt) {}
