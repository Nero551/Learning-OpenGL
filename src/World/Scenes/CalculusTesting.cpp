#include "CalculusTesting.hpp"

#include <complex>

#include "Core/InnerCore/Engine.hpp"
#include "Core/OuterCore/Service.hpp"
#include "Core/Services/ResourceManager.hpp"
#include "Modules/Renderer/Primitives/Primitives.hpp"
#include "Modules/Renderer/Resources/Material.hpp"
#include "Utilities/Math/Function.hpp"
#include "World/Novas/Light.hpp"
#include "World/Novas/MeshInstance3D.hpp"

namespace E {
static float max = 100;
static float min = -100;

MeshInstance3D& CalculusTesting::CreatePoint(Vector4 col) {
    auto& resourceManager = Service::Get<ResourceManager>();
    auto& mesh = Primitives::CreateCube("point");
    auto& material = resourceManager.Load<Material>(std::format("m{}{}{}", col.z, col.x, col.y));
    material.Color = col;
    auto& shader = resourceManager.Load<Shader>("shader");

    shader.AssignSource(
        resourceManager.Load<ShaderSource>("pointVert", "Assets/Shaders/shader.vert", ShaderStage::Vertex));
    shader.AssignSource(
        resourceManager.Load<ShaderSource>("pointFrag", "Assets/Shaders/shader.frag", ShaderStage::Fragment));
    material.Shader = &shader;

    auto& point = World::Get().CreateEntity<MeshInstance3D>();
    point.GetComponent<MeshComponent>().Mesh = &mesh;
    point.GetComponent<MaterialComponent>().Material = &material;
    point.GetComponent<Transform3DComponent>().LocalScale = Vector3(0.75);
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
    Engine::Get().World.CreateEntity<Entity>();
    World::Get().CreateEntity<Nova3D>();

    SetRoot(World::Get().CreateEntity<Nova3D>());

    float max = 4;

    for (float x = 0; x < max; x += 1) {
        for (float y = 0; y < max; y += 1) {
            for (float z = 0; z < max; z += 1) {
                Plot(
                    {x, y, z},
                    {x / 20.0f, y / 20.0f, z / 20.0f, 1}
                );
            }
        }
    }
}

static constexpr float step = 0.025;
static constexpr float xRange = 5;
static float x = -5;

void CalculusTesting::FixedUpdate(double fdt) {
    // auto& resourceManager = Service::Get<ResourceManager>();
    if (x > xRange) {
        return;
    }
    x += step;
    //
    // Function piecewise = [](const float x) {
    //     float y = 0;
    //
    //     if (x < 0) {
    //         y = std::cos(x);
    //     }
    //     else {
    //         y = std::sin(x);
    //     }
    //
    //     return y;
    // };
    //
    // Plot({x, piecewise(x), 0}, {1, 0, 0, 1});
    // // Plot({x, f.Derivative(x), 1}, {0, 1, 0, 1});
    // // Plot({x, f.Differentiate().Derivative(x), 2}, {0, 0, 1, 1});
}
}
