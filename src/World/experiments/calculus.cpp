#include "calculus.hpp"

#include "Core/InnerCore/Engine.hpp"
#include "Core/InnerCore/World.hpp"
#include "Core/Services/ResourceManager.hpp"
#include "Modules/Input/Input.hpp"
#include "Modules/Input/Enums/Keys.hpp"
#include "Modules/Renderer/Primitives/Primitives.hpp"
#include "Utilities/Math/Function.hpp"
#include "Utilities/Math/Vector/Vector4.hpp"
#include "World/Novas/Light.hpp"
#include "World/Novas/MeshInstance3D.hpp"

namespace E {
static MeshInstance3D& CreatePoint(M::Vector4 col) {
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
    point.GetComponent<Transform3DComponent>().Scale = {0.75};
    World::Get().Root->AttachChild(point);

    return point;
}

static float max = 100;
static float min = -100;

static void Plot(M::Vector3 vec3, M::Vector4 col) {
    if (vec3.y < max && vec3.y > min) {
        const auto& point = CreatePoint(col);
        auto& transform = point.GetComponent<Transform3DComponent>();
        transform.Position.x = vec3.x;
        transform.Position.y = vec3.y;
        transform.Position.z = vec3.z;
    }
}

static int lightId = 0;

void calculus::Start() {
    auto& resourceManager = Service::Get<ResourceManager>();
    float max = 5;

    // for (float x = 0; x < max; x += 1) {
    //     for (float y = 0; y < max; y += 1) {
    //         for (float z = 0; z < max; z += 1) {
    //             Plot(
    //                 {x, y, z},
    //                 {x / 10.0f, y / 10.0f, z / 10.0f, 1}
    //             );
    //         }
    //     }
    // }
}


static constexpr float step = 0.025;
static constexpr float xRange = 10;
static float x = 0;

void calculus::Update(double dt) {
    auto& resourceManager = Service::Get<ResourceManager>();

    if (x > xRange) {
        return;
    }
    x += step;

    M::Function f = [](const float x) {
        return x;
    };

    Plot({x, f(x), 0}, {1, 0, 0, 1});
    Plot({x, f.Derivative(x), 0}, {1, 0, 0, 1});
    Plot({x, f.Integral(0, x), 0}, {1, 0, 0, 1});
}
}
