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
static MeshInstance3D& CreatePoint(Vector4 col) {
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
    point.GetComponent<Transform3DComponent>().Scale = Vector3(0.75);
    World::Get().Root->AttachChild(point);

    return point;
}

static float max = 100;
static float min = -100;

static void Plot(Vector3 vec3, Vector4 col) {
    if (vec3.y < max && vec3.y > min) {
        const auto& point = CreatePoint(col);
        Logger::Info(point.Id);
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


    // Plot({0, 0, 0}, {0.3, 0.3, 0.3, 1});

    for (float x = 0; x < max; x += 1) {
        for (float y = 0; y < max; y += 1) {
            for (float z = 0; z < max; z += 1) {
                Plot(
                    {x, y, z},
                    {x / 10.0f, y / 10.0f, z / 10.0f, 1}
                );
            }
        }
    }


    // auto& lightShader = resourceManager.Load<Shader>("lightShader");
    // lightShader.AssignSource(resourceManager.Load<ShaderSource>("lightFrag", "Assets/Shaders/lightShader.frag",
    //     ShaderStage::Fragment));
    // lightShader.AssignSource(
    //     resourceManager.Load<ShaderSource>("lightVert", "Assets/Shaders/lightShader.vert", ShaderStage::Vertex));
    //
    // auto& lightMaterial = resourceManager.Load<Material>("lightMaterial");
    // lightMaterial.Emission = 1;
    // lightMaterial.Color = {1, 1, 1, 1};
    // lightMaterial.Shader = &lightShader;
    // auto& mesh = Primitives::CreateCube("point");
    //
    //
    // auto& light = World::Get().CreateEntity<Light>();
    // light.AddComponent<MaterialComponent>().Material = &lightMaterial;
    // light.AddComponent<MeshComponent>().Mesh = &mesh;
    // light.GetComponent<LightComponent>().Type = LightType::Spot;
    // light.GetComponent<LightComponent>().Intensity = 1;
    // World::Get().Root->AttachChild(light);
    // lightId = light.Id;
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

    Function f = [](const float x) {
        return x;
    };
}
}
