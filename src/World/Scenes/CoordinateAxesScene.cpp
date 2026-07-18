#include "CoordinateAxesScene.hpp"

#include "Core/InnerCore/Engine.hpp"
#include "Core/Services/ResourceManager.hpp"
#include "Modules/Renderer/Components/MaterialComponent.hpp"
#include "Modules/Renderer/Components/MeshComponent.hpp"
#include "Modules/Renderer/Primitives/Primitives.hpp"
#include "Utilities/Math/Color.hpp"
#include "World/Entities/Axis.hpp"

CoordinateAxesScene::CoordinateAxesScene() {
    auto& resourceManager = ServiceStore::Ins->Get<ResourceManager>();

    SetRoot(Engine::Get().World.CreateEntity<Entity>());

    auto& shader = ServiceStore::Ins->Get<ResourceManager>().Load<Shader>("AxisShader",
        "Assets/Shaders/axisShader.frag",
        "Assets/Shaders/axisShader.vert");
    auto& line = Primitives::CreateLine("Line");

    auto& xAxis = Engine::Get().World.CreateEntity<Axis>();
    xAxis.GetComponent<MeshComponent>().Mesh = &line;
    xAxis.GetComponent<MaterialComponent>().Material = &resourceManager.Load<Material>("X-Axis Material");
    xAxis.GetComponent<MaterialComponent>().Material->Shader = &shader;

    xAxis.GetComponent<Transform3DComponent>().LocalEulerRotation = {0, Math::Radians(90), 0};
    xAxis.GetComponent<Transform3DComponent>().LocalPosition = {-50, 0, 0};
    xAxis.GetComponent<Transform3DComponent>().LocalScale = {1, 1, 200};
    xAxis.GetComponent<MaterialComponent>().Material->Color = Color::Red;

    GetRoot().AttachChild(xAxis);

    auto& yAxis = Engine::Get().World.CreateEntity<Axis>();
    yAxis.GetComponent<MeshComponent>().Mesh = &line;
    yAxis.GetComponent<MaterialComponent>().Material = &resourceManager.Load<Material>("Y-Axis Material");
    yAxis.GetComponent<MaterialComponent>().Material->Shader = &shader;

    yAxis.GetComponent<Transform3DComponent>().LocalEulerRotation = {Math::Radians(-90), 0, 0};
    yAxis.GetComponent<Transform3DComponent>().LocalPosition = {0, -50, 0};
    yAxis.GetComponent<Transform3DComponent>().LocalScale = {1, 1, 200};
    yAxis.GetComponent<MaterialComponent>().Material->Color = Color::Green;

    GetRoot().AttachChild(yAxis);

    auto& zAxis = Engine::Get().World.CreateEntity<Axis>();
    zAxis.GetComponent<MeshComponent>().Mesh = &line;
    zAxis.GetComponent<MaterialComponent>().Material = &resourceManager.Load<Material>("Z-Axis Material");
    zAxis.GetComponent<MaterialComponent>().Material->Shader = &shader;

    zAxis.GetComponent<Transform3DComponent>().LocalEulerRotation = {0, 0, 0};
    zAxis.GetComponent<Transform3DComponent>().LocalPosition = {0, 0, -50};
    zAxis.GetComponent<Transform3DComponent>().LocalScale = {1, 1, 200};
    zAxis.GetComponent<MaterialComponent>().Material->Color = Color::Blue;

    GetRoot().AttachChild(zAxis);
}

void CoordinateAxesScene::Update(double dt) {}
