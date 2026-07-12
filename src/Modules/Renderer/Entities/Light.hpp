#pragma once
#include "../Components/MaterialComponent.hpp"
#include "../Components/MeshComponent.hpp"
#include "../Resources/Mesh.hpp"
#include "../Vertex.hpp"
#include "Core/Engine.hpp"
#include "Core/Entity.hpp"

struct Light : Entity {
   void Initialize() override {
      AddComponent<MeshComponent>();
      AddComponent<TransformComponent>();
      AddComponent<MaterialComponent>();
   }
};
