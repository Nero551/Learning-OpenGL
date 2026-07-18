#include "Renderer.hpp"

#include "Components/CameraComponent.hpp"
#include "Components/MaterialComponent.hpp"
#include "Components/MeshComponent.hpp"
#include "../../World/Components/Transform3DComponent.hpp"
#include "Core/InnerCore/Engine.hpp"
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
    auto& scene = Engine::Get().World.ActiveScene;
    auto& camera = scene->GetActiveCamera();

    Matrix4 projection = camera.GetComponent<CameraComponent>().GetProjectionMatrix();
    Matrix4 view = GetSystem<CameraSystem>().GetViewMatrix();

    for (auto& entity : scene->GetRoot().GetDescendants()) {
        if (!entity->HasComponent<Transform3DComponent>()) {
            continue;
        }
        auto& transformComponent = entity->GetComponent<Transform3DComponent>();

        if (entity->HasComponent<MaterialComponent>()) {
            auto& materialComponent = entity->GetComponent<MaterialComponent>();
            materialComponent.Material->Use();


            materialComponent.Material->Shader->SetUniform(
                FloatUniform("Time", static_cast<float>(Engine::Get().Time)));

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
