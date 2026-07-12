#pragma once
#include <unordered_map>

#include "Entity.hpp"
#include "Modules/Renderer/Entities/Camera.hpp"

template<typename T>concept EntityType = std::derived_from<T, Entity>;

struct Scene {
   std::string Name;
   std::unordered_map<unsigned int, std::unique_ptr<Entity> > Entities;

   Scene() = default;

   virtual ~Scene() = default;

   Scene(const Scene &) = delete;

   Scene &operator=(const Scene &) = delete;

   Scene(Scene &&) = default;

   Scene &operator=(Scene &&) = default;

   virtual void Initialize() {}

   void SetActiveCamera(Camera &camera) { ActiveCamera = &camera; }
   Camera &GetActiveCamera() { return static_cast<Camera &>(*ActiveCamera); }


   template<EntityType T> T &CreateEntity() {
      auto entity = std::make_unique<T>();
      entity->Id = id;
      entity->Initialize();

      T &ref = *entity;

      Entities.insert({id, std::move(entity)});

      id++;

      return ref;
   }

   template<EntityType T> T &GetEntity(unsigned int id) {
      auto entity = Entities.find(id);
      if (entity == Entities.end()) {
         throw std::runtime_error(std::format("Entity Not Found: {}", typeid(T).name()));
      }
      return static_cast<T &>((*entity->second));
   }

private:
   Camera *ActiveCamera = nullptr;
   unsigned int id = 1;
};
