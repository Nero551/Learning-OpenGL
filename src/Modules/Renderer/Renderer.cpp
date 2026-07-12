#include "Renderer.hpp"
#include "Components/MaterialComponent.hpp"
#include "Components/MeshComponent.hpp"
#include "Core/Engine.hpp"
#include "Systems/CameraSystem.hpp"

#include <ranges>

#include "Uniforms/FloatUniform.hpp"
#include "Uniforms/IntUniform.hpp"
#include "Uniforms/Matrix3Uniform.hpp"
#include "Uniforms/Matrix4Uniform.hpp"
#include "Uniforms/Vector3Uniform.hpp"

void Renderer::AddSystems() {
   AddSystem<CameraSystem>();
}

void Renderer::OnRender() {
   auto &scene = Engine::Ins->World.GetActiveScene();
   auto &camera = scene.GetActiveCamera();

   Matrix4 projection = camera.GetComponent<CameraComponent>().GetProjectionMatrix();
   Matrix4 view = GetSystem<CameraSystem>().GetViewMatrix();

   for (auto &entity: scene.Entities | std::views::values) {
      if (!entity->HasComponent<TransformComponent>()) {
         continue;
      }
      auto &transformComponent = entity->GetComponent<TransformComponent>();


      if (entity->HasComponent<MaterialComponent>()) {
         auto &materialComponent = entity->GetComponent<MaterialComponent>();
         materialComponent.Material->GetShader().SetUniform(FloatUniform("Time", Engine::Ins->Time));

         materialComponent.Material->GetShader().SetUniform(Matrix4Uniform("ModelMatrix",
            transformComponent.GetModelMatrix()));

         materialComponent.Material->GetShader().SetUniform(Matrix4Uniform("ViewMatrix", view));

         materialComponent.Material->GetShader().SetUniform(Matrix4Uniform("ProjectionMatrix", projection));

         materialComponent.Material->GetShader().SetUniform(Matrix3Uniform("NormalMatrix",
            transformComponent.GetNormalMatrix()));

         materialComponent.Material->GetShader().SetUniform(Vector3Uniform("ViewPosition",
            camera.GetComponent<TransformComponent>().Position));

         materialComponent.Material->Use();
      }

      if (entity->HasComponent<MeshComponent>()) {
         auto &meshComponent = entity->GetComponent<MeshComponent>();
         meshComponent.Mesh->Draw();
      }
   }
}
