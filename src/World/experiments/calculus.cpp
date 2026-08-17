#include "calculus.hpp"

#include "Core/InnerCore/Engine.hpp"
#include "Core/InnerCore/World.hpp"
#include "Core/Services/ResourceManager.hpp"
#include "Math/Common/Exponentials.hpp"
#include "Math/Common/Random.hpp"
#include "Math/Functions/Function.hpp"
#include "Math/Vector/Vector4.hpp"
#include "Modules/Renderer/Primitives/Primitives.hpp"
#include "World/Novas/Light.hpp"
#include "World/Novas/MeshInstance3D.hpp"

namespace E {
static MeshInstance3D& CreatePoint(M::Vector4 col) {
    auto& resourceManager = Service::Get<ResourceManager>();
    auto& mesh = Primitives::CreateCube("point");
    auto& material = resourceManager.Load<Material>(std::format("m{}{}{}", col.z, col.x, col.y));
    material.Color = col;
    auto& shader = resourceManager.Load<Shader>("shader");

    shader.AssignSource(resourceManager.Load<ShaderSource>("pointVert", "Assets/Shaders/shader.vert", ShaderStage::Vertex));
    shader.AssignSource(resourceManager.Load<ShaderSource>("pointFrag", "Assets/Shaders/shader.frag", ShaderStage::Fragment));
    material.Shader = &shader;

    mesh.RenderMode = RenderMode::SolidWireframe;

    auto& point = World::Get().CreateEntity<MeshInstance3D>();
    point.GetComponent<MeshComponent>().Mesh = &mesh;
    point.GetComponent<MaterialComponent>().Material = &material;
    point.GetComponent<Transform3DComponent>().Scale = { 0.75 };
    World::Get().Root->AttachChild(point);

    return point;
}

static float max = 100;
static float min = -100;

static void Plot(M::Vector3 vec3, M::Vector4 col = { 1, 1, 1, 1 }) {
    if (vec3.y < max && vec3.y > min) {
        const auto& point = CreatePoint(col);
        auto& transform = point.GetComponent<Transform3DComponent>();
        transform.Position.x = vec3.x;
        transform.Position.y = vec3.y;
        transform.Position.z = vec3.z;
    }
}

static int entityId = 0;

void calculus::Start() {
    auto& resourceManager = Service::Get<ResourceManager>();
    float max = 5;

    // TODO- put all entities in namespace E , components in C and systems in S .
    // rename global namespace to N
    //
    //  for (float x = 0; x < max; x += 1) {
    //      for (float y = 0; y < max; y += 1) {
    //          for (float z = 0; z < max; z += 1) {
    //              Plot(
    //                  {x, y, z},
    //                  {x / 10.0f, y / 10.0f, z / 10.0f, 1}
    //              );
    //          }
    //      }
    //  }

    // auto& point = CreatePoint({0.7, 0.7, 0.7, 1});
    // entityId = point.Id;
}

static constexpr float step = 0.025;
static constexpr float xRange = 8;
static float x = -8;

static float elapsed = 0;
static float passed = 0;

void calculus::Update(double dt) {
    auto& resourceManager = Service::Get<ResourceManager>();

    x += step;
    if (x >= xRange) {
        return;
    }

    M::Function f = [](const float x) { return 2 * x; };

    M::Function g = [](const float x) { return M::Pow(x, 2); };
    Plot({ x, f(x), 0 });
    Plot({ x, f.Integral(3, x), -2 }, { 0, 0, 1, 1 });
    Plot({ x, g(x), 2 }, { 1, 0, 0, 1 });
}
} // namespace E

//
// M::Vector3 Tween(M::Vector3 start, M::Vector3 end, float duration, double dt)
// {
//     passed += dt;
//     float t = M::Clamp(passed / duration, 0, 1);
//     M::Vector3 current = start.Lerp(end, M::EaseOutQuad(t));
//     return current;
// }
