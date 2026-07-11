#pragma once
#include "Entity.hpp"
#include "Modules/Renderer/Entities/Camera.hpp"
#include <unordered_map>
#include <vector>

template<typename T>concept EntityType = std::derived_from<T, Entity>;

struct Scene {
   std::string Name;
   Camera *ActiveCamera = nullptr;
   std::unordered_map<unsigned int, std::unique_ptr<Entity> > Entities;

   Scene() = default;

   virtual ~Scene() = default;

   Scene(const Scene &) = delete;

   Scene &operator=(const Scene &) = delete;

   Scene(Scene &&) = default;

   Scene &operator=(Scene &&) = default;

   virtual void Initialize() {
   }

   void SetActiveCamera(Camera &camera) { ActiveCamera = &camera; }

   template<EntityType T> T &CreateEntity() {
      auto entity = std::make_unique<T>();
      entity->Id = id;
      entity->Initialize();

      T &ref = *entity;

      Entities.insert({id, std::move(entity)});

      id++;

      return ref;
   }

private:
   unsigned int id = 1;
};
