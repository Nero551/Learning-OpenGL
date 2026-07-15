#include "LightingSystem.hpp"

#include "../Components/LightComponent.hpp"
#include "../Components/MaterialComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Uniforms/FloatUniform.hpp"
#include "../Uniforms/IntUniform.hpp"
#include "../Uniforms/Vector3Uniform.hpp"
#include "Modules/Renderer/Entities/Camera.hpp"


void LightingSystem::Start() {}

void LightingSystem::Render() {
    auto& scene = Engine::Ins->World.ActiveScene;
    auto& camera = scene->GetActiveCamera<Camera>();

    for (auto& entity : scene->GetEntities()) {
        if (!entity->HasComponent<TransformComponent>()) { continue; }

        if (!entity->HasComponent<MaterialComponent>()) { continue; }
        auto& materialComponent = entity->GetComponent<MaterialComponent>();

        materialComponent.Material->Shader->SetUniform(IntUniform("MaxLights", scene->MaxLights));
        materialComponent.Material->Shader->SetUniform(Vector3Uniform("ViewPosition",
            camera.GetComponent<TransformComponent>().Position));

        for (int i = 0; i < scene->Lights.size(); i++) {
            auto& light = scene->Lights[i];
            auto& lightComponent = light->GetComponent<LightComponent>();

            materialComponent.Material->Shader->SetUniform(
                Vector3Uniform(std::format("Lights[{}].Color", i), lightComponent.Color));

            materialComponent.Material->Shader->SetUniform(
                Vector3Uniform(std::format("Lights[{}].Position", i),
                    light->GetComponent<TransformComponent>().Position));

            materialComponent.Material->Shader->SetUniform(
                Vector3Uniform(std::format("Lights[{}].Ambient", i), lightComponent.Ambient));

            materialComponent.Material->Shader->SetUniform(
                Vector3Uniform(std::format("Lights[{}].Diffuse", i), lightComponent.Diffuse));

            materialComponent.Material->Shader->SetUniform(
                Vector3Uniform(std::format("Lights[{}].Specular", i), lightComponent.Specular));

            materialComponent.Material->Shader->SetUniform(
                IntUniform(std::format("Lights[{}].Type", i),
                    static_cast<int>(lightComponent.Type)));

            materialComponent.Material->Shader->SetUniform(
                Vector3Uniform(std::format("Lights[{}].Direction", i),
                    light->GetComponent<TransformComponent>().GetForward()));

            materialComponent.Material->Shader->SetUniform(
                FloatUniform(std::format("Lights[{}].Constant", i), lightComponent.Constant));

            materialComponent.Material->Shader->SetUniform(
                FloatUniform(std::format("Lights[{}].Linear", i), lightComponent.Linear));

            materialComponent.Material->Shader->SetUniform(
                FloatUniform(std::format("Lights[{}].Quadratic", i), lightComponent.Quadratic));

            materialComponent.Material->Shader->SetUniform(
                FloatUniform(std::format("Lights[{}].Intensity", i), lightComponent.Intensity));

            materialComponent.Material->Shader->SetUniform(
                FloatUniform(std::format("Lights[{}].InnerCutOff", i),
                    std::cos(lightComponent.InnerCutOff)));

            materialComponent.Material->Shader->SetUniform(
                FloatUniform(std::format("Lights[{}].OuterCutOff", i),
                    std::cos(lightComponent.OuterCutOff)));
        }
    }
}
