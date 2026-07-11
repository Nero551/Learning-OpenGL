#include "Renderer.hpp"
#include "Components/MaterialComponent.hpp"
#include "Components/MeshComponent.hpp"
#include "Core/Engine.hpp"
#include "Systems/CameraSystem.hpp"

#include <ranges>

#include "Uniforms/FloatUniform.hpp"
#include "Uniforms/Matrix4Uniform.hpp"

void Renderer::Start() {}

void Renderer::Update(double dt) {}

void Renderer::Render() {
   auto *scene = Engine::Ins->World.ActiveScene;
   auto *camera = scene->ActiveCamera;

   Matrix4 projection = camera->GetComponent<CameraComponent>().GetProjectionMatrix();
   Matrix4 view = Engine::Ins->World.GetSystem<CameraSystem>().GetViewMatrix();

   for (auto &entity: scene->Entities | std::views::values) {
      if (!entity->HasComponent<TransformComponent>()) {
         continue;
      }
      auto &transformComponent = entity->GetComponent<TransformComponent>();


      if (entity->HasComponent<MaterialComponent>()) {
         auto &materialComponent = entity->GetComponent<MaterialComponent>();
         materialComponent.Material->Shader->SetUniform(FloatUniform("Time", glfwGetTime()));

         materialComponent.Material->Shader->SetUniform(Matrix4Uniform("uModel",
            transformComponent.GetModelMatrix()));

         materialComponent.Material->Shader->SetUniform(Matrix4Uniform("uView", view));

         materialComponent.Material->Shader->SetUniform(Matrix4Uniform("uProjection", projection));

         materialComponent.Material->Use();
      }

      if (entity->HasComponent<MeshComponent>()) {
         auto &meshComponent = entity->GetComponent<MeshComponent>();
         meshComponent.Mesh->Draw();
      }
   }
}

void Renderer::Stop() {}
