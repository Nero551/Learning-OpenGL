#include "Renderer.hpp"
#include "Components/MaterialComponent.hpp"
#include "Components/MeshComponent.hpp"
#include "Core/Engine.hpp"
#include "Systems/CameraSystem.hpp"

#include <ranges>

void Renderer::Start() {
}

void Renderer::Update(double dt) {
}

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
         materialComponent.Material->Use();
         materialComponent.Material->Shader->SetMat4("uModel", transformComponent.GetModelMatrix());
         materialComponent.Material->Shader->SetMat4("uView", view);
         materialComponent.Material->Shader->SetMat4("uProjection", projection);
      }

      if (entity->HasComponent<MeshComponent>()) {
         auto &meshComponent = entity->GetComponent<MeshComponent>();
         meshComponent.Mesh->Draw();
      }
   }
}

void Renderer::Stop() {
}
