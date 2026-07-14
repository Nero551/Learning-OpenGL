#pragma once
#include "Core/Entity.hpp"
#include "Modules/Renderer/Components/MaterialComponent.hpp"
#include "Modules/Renderer/Components/MeshComponent.hpp"
#include "Modules/Renderer/Components/TransformComponent.hpp"

struct Axis : Entity {
   void Initialize() override {
      AddComponent<MeshComponent>();
      AddComponent<MaterialComponent>();
      AddComponent<TransformComponent>();
   }
};
