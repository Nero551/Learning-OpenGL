#include "CalculusTesting.hpp"

#include <cmath>

#include "Core/InnerCore/Engine.hpp"
#include "Core/OuterCore/ServiceStore.hpp"
#include "Core/Services/ResourceManager.hpp"
#include "Modules/Renderer/Primitives/Primitives.hpp"
#include "Modules/Renderer/Resources/Material.hpp"
#include "World/Novas/Light.hpp"
#include "World/Novas/MeshInstance3D.hpp"

static Mesh* mesh;
static Material* material;
static float max = 100;
static float min = -100;

MeshInstance3D& CalculusTesting::CreatePoint() {
    auto& point = Engine::Get().World.CreateEntity<MeshInstance3D>();
    point.GetComponent<MeshComponent>().Mesh = mesh;
    point.GetComponent<MaterialComponent>().Material = material;
    point.GetComponent<Transform3DComponent>().LocalScale = Vector3(0.2);
    GetRoot().AttachChild(point);

    return point;
}

void CalculusTesting::Plot(Vector3 vec3) {
    if (vec3.y < max && vec3.y > min) {
        const auto& point = CreatePoint();
        auto& transform = point.GetComponent<Transform3DComponent>();
        transform.LocalPosition->x = vec3.x;
        transform.LocalPosition->y = vec3.y;
        transform.LocalPosition->z = vec3.z;
    }
}

CalculusTesting::CalculusTesting() {
    auto& resourceManager = ServiceStore::Ins->Get<ResourceManager>();
    mesh = &Primitives::CreateCube("point");
    material = &resourceManager.Load<Material>("material");
    auto& shader = resourceManager.Load<Shader>("shader");

    shader.AssignSource(
        resourceManager.Load<ShaderSource>("pointVert", "Assets/Shaders/shader.vert", ShaderStage::Vertex));
    shader.AssignSource(
        resourceManager.Load<ShaderSource>("pointFrag", "Assets/Shaders/shader.frag", ShaderStage::Fragment));
    material->Shader = &shader;

    SetRoot(Engine::Get().World.CreateEntity<Nova3D>());
}

static constexpr float dx = 0.001f;

static float f(const float x) {
    float y = 0;
    // y = (0.148f * x * x + 0.6f * x - 0.013f) * std::sin(x / 2.58f) * 1.2516f;
    // y = 1.0f / (0.6f * x * x + 0.09f * x + 1.0f);
    // y = x * x * x / 12;
    y = sin(x);
    return y;
}

static float g(const float x) {
    float y = (f(x + dx) - f(x)) / dx;
    Logger::Info(y);
    return y;
}

static constexpr float step = 0.025;
static constexpr float xRange = 15;
static float x = 0;

void CalculusTesting::FixedUpdate(double fdt) {
    if (x > xRange) {
        return;
    }
    x += step;

    Plot({x, f(x), 0});
    Plot({x, g(x), 0});
}
