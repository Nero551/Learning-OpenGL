#pragma once
#include "Core/Entity.hpp"
#include "Modules/Renderer/Components/MaterialComponent.hpp"
#include "Modules/Renderer/Components/MeshComponent.hpp"
#include "Modules/Renderer/Components/TransformComponent.hpp"

struct Cube : Entity {
  void Initialize() override {
    AddComponent<TransformComponent>();
    AddComponent<MeshComponent>();
    AddComponent<MaterialComponent>();
  }
};