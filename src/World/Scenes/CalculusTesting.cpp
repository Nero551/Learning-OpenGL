#include "CalculusTesting.hpp"

#include <cassert>
#include <cmath>

#include "Core/InnerCore/Engine.hpp"
#include "Core/OuterCore/ServiceStore.hpp"
#include "Core/Services/ResourceManager.hpp"
#include "Modules/Renderer/Primitives/Primitives.hpp"
#include "Modules/Renderer/Resources/Material.hpp"
#include "Utilities/Math/Function.hpp"
#include "World/Novas/Light.hpp"
#include "World/Novas/MeshInstance3D.hpp"

static float max = 100;
static float min = -100;

MeshInstance3D& CalculusTesting::CreatePoint(Vector4 col) {
    auto& resourceManager = ServiceStore::Ins->Get<ResourceManager>();
    auto& mesh = Primitives::CreateCube("point");
    auto& material = resourceManager.Load<Material>(std::format("m{}{}{}", col.z, col.x, col.y));
    material.Color = col;
    auto& shader = resourceManager.Load<Shader>("shader");

    shader.AssignSource(
        resourceManager.Load<ShaderSource>("pointVert", "Assets/Shaders/shader.vert", ShaderStage::Vertex));
    shader.AssignSource(
        resourceManager.Load<ShaderSource>("pointFrag", "Assets/Shaders/shader.frag", ShaderStage::Fragment));
    material.Shader = &shader;


    auto& point = Engine::Get().World.CreateEntity<MeshInstance3D>();
    point.GetComponent<MeshComponent>().Mesh = &mesh;
    point.GetComponent<MaterialComponent>().Material = &material;
    point.GetComponent<Transform3DComponent>().LocalScale = Vector3(0.2);
    GetRoot().AttachChild(point);

    return point;
}

void CalculusTesting::Plot(Vector3 vec3, Vector4 col) {
    if (vec3.y < max && vec3.y > min) {
        const auto& point = CreatePoint(col);
        auto& transform = point.GetComponent<Transform3DComponent>();
        transform.LocalPosition->x = vec3.x;
        transform.LocalPosition->y = vec3.y;
        transform.LocalPosition->z = vec3.z;
    }
}

CalculusTesting::CalculusTesting() {
    SetRoot(Engine::Get().World.CreateEntity<Nova3D>());
}

static constexpr float step = 0.025;
static constexpr float xRange = 5;
static float x = -5;

void CalculusTesting::FixedUpdate(double fdt) {
    auto& resourceManager = ServiceStore::Ins->Get<ResourceManager>();
    if (x > xRange) {
        return;
    }
    x += step;


    Function f = [](const float x) {
        float y = std::pow(2, x);

        return y;
    };

    Function g = [](const float x) {
        float y = std::exp(x);
        return y;
    };

    Plot({x, g.Derivative(x), 1}, {0, 1, 0, 1});
    Plot({x, g(x), 0}, {1, 0, 0, 1});
    // Plot({x, s(x), 2}, {0, 0, 1, 1});
    // Plot({x, f(x), 0}, {1, 0, 0, 1});
    // Plot({x, d.Derivative(x), 0}, {0, 1, 1, 1});
    // Plot({x, f.Derivative(x), 1}, {0, 0, 1, 1});
    // Plot({x, f.Derivative(x), 1}, {0, 0, 1, 1});
    // Plot({x, f.Derivative(x), 0}, {0, 1, 0, 1});
    // Plot({x, d(g, x) * d(s, x), 0}, {0, 0, 1, 1});
    // Plot({x, d(f, x), 0});
}
