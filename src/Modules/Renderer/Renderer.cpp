#include "Renderer.hpp"
#include "Components/MaterialComponent.hpp"
#include "Components/MeshComponent.hpp"
#include "Core/InnerCore/Engine.hpp"
#include "Entities/Camera.hpp"
#include "Systems/CameraSystem.hpp"

#include "Primitives/Primitives.hpp"
#include "Systems/LightingSystem.hpp"
#include "Uniforms/FloatUniform.hpp"
#include "Uniforms/Matrix3Uniform.hpp"
#include "Uniforms/Matrix4Uniform.hpp"

void Renderer::AddSystems() {
    AddSystem<CameraSystem>();
    AddSystem<LightingSystem>();
}

void Renderer::OnRender() {
    auto& scene = Engine::Ins->World.ActiveScene;
    auto& camera = scene->GetActiveCamera();

    Matrix4 projection = camera.GetComponent<CameraComponent>().GetProjectionMatrix();
    Matrix4 view = GetSystem<CameraSystem>().GetViewMatrix();

    for (auto& entity : scene->GetRoot().GetDescendants()) {
        if (!entity->HasComponent<TransformComponent>()) {
            continue;
        }
        auto& transformComponent = entity->GetComponent<TransformComponent>();

        if (entity->HasComponent<MaterialComponent>()) {
            auto& materialComponent = entity->GetComponent<MaterialComponent>();
            materialComponent.Material->Use();


            materialComponent.Material->Shader->SetUniform(FloatUniform("Time", static_cast<float>(Engine::Ins->Time)));

            materialComponent.Material->Shader->SetUniform(
                Matrix4Uniform("ModelMatrix", transformComponent.GetModelMatrix()));

            materialComponent.Material->Shader->SetUniform(Matrix4Uniform("ViewMatrix", view));

            materialComponent.Material->Shader->SetUniform(Matrix4Uniform("ProjectionMatrix", projection));

            materialComponent.Material->Shader->SetUniform(
                Matrix3Uniform("NormalMatrix", transformComponent.GetNormalMatrix()));
        }

        if (entity->HasComponent<MeshComponent>()) {
            auto& meshComponent = entity->GetComponent<MeshComponent>();

            meshComponent.Mesh->Draw();
        }
    }
}
