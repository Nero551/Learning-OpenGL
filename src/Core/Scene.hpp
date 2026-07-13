#pragma once
#include <unordered_map>

#include "Entity.hpp"
#include "Modules/Renderer/Entities/Camera.hpp"
#include "Utilities/Services/LoggerService.hpp"

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

   virtual void Update(double dt) {}
   virtual void Render() {}
   virtual void BeginFrame(double dt) {}
   virtual void EndFrame(double dt) {}
   virtual void Stop() {}

   void SetActiveCamera(Camera &camera) { ActiveCamera = &camera; }

   Camera &GetActiveCamera() {
      return LoggerService::Require(ActiveCamera, "Scene Has No Active Camera");
   }


   template<EntityType T> T &CreateEntity() {
      auto entity = std::make_unique<T>();
      entity->Id = currentEntityId;
      entity->Initialize();

      T &ref = *entity;

      Entities.insert({currentEntityId, std::move(entity)});

      currentEntityId++;

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
   unsigned int currentEntityId = 1;
};
