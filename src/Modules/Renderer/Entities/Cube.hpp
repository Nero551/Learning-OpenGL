#pragma once
#include "Core/Entity.hpp"
#include "Modules/Renderer/Components/MaterialComponent.hpp"
#include "Modules/Renderer/Components/MeshComponent.hpp"
#include "Modules/Renderer/Components/TransformComponent.hpp"

struct Cube : Entity {
   void Initialize() override {
      auto &mesh = Engine::Ins->ResourceManager.Load<Mesh>("mesh", std::vector<Vertex>{
         // front face
         Vertex({-0.5, -0.5, 0.5, 1}, {1, 0, 0, 1}, {0, 0}),
         // 0
         Vertex({0.5, -0.5, 0.5, 1}, {1, 0, 1, 1}, {1, 0}),
         // 1
         Vertex({0.5, 0.5, 0.5, 1}, {0, 1, 0, 1}, {1, 1}),
         // 2
         Vertex({-0.5, 0.5, 0.5, 1}, {1, 1, 1, 1}, {0, 1}),
         // 3

         // back face
         Vertex({-0.5, -0.5, -0.5, 1}, {1, 0, 0, 1}, {1, 0}),
         // 4
         Vertex({0.5, -0.5, -0.5, 1}, {0, 0, 1, 1}, {0, 0}),
         // 5
         Vertex({0.5, 0.5, -0.5, 1}, {0, 1, 0, 1}, {0, 1}),
         // 6
         Vertex({-0.5, 0.5, -0.5, 1}, {1, 1, 1, 1}, {1, 1}) // 7
      }, std::vector<unsigned int>{
         0, 1, 2, 2, 3, 0,

         // back
         5, 4, 7, 7, 6, 5,

         // left
         4, 0, 3, 3, 7, 4,

         // right
         1, 5, 6, 6, 2, 1,

         // top
         3, 2, 6, 6, 7, 3,

         // bottom
         4, 5, 1, 1, 0, 4
      });

      AddComponent<TransformComponent>();
      auto &meshComponent = AddComponent<MeshComponent>();
      AddComponent<MaterialComponent>();

      meshComponent.Mesh = &mesh;
   }
};
