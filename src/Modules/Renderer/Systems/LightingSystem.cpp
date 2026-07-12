#include "LightingSystem.hpp"

#include "../Components/MaterialComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Uniforms/Vector3Uniform.hpp"


void LightingSystem::Render() {
   auto &scene = Engine::Ins->World.GetActiveScene();
   auto &camera = scene.GetActiveCamera();

   for (auto &entity: scene.Entities | std::views::values) {
      if (!entity->HasComponent<TransformComponent>()) {
         continue;
      }
      auto &transformComponent = entity->GetComponent<TransformComponent>();

      if (entity->HasComponent<MaterialComponent>()) {
         auto &materialComponent = entity->GetComponent<MaterialComponent>();

         materialComponent.Material->GetShader().SetUniform(Vector3Uniform("ViewPosition",
            camera.GetComponent<TransformComponent>().Position));
      }
   }
}
