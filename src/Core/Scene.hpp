#pragma once

#include "Entity.hpp"
#include "Modules/Renderer/Entities/Camera.hpp"
#include "Utilities/SafePtr.hpp"
#include <unordered_map>
#include <format>
#include <vector>


template <typename T>concept EntityType = std::derived_from<T, Entity>;

struct Scene
{
   std::string Name;
   SafePtr<Camera> ActiveCamera{"Scene Has No Active Camera Assigned"};
   std::unordered_map<unsigned int, std::unique_ptr<Entity>> Entities;

   Scene() = default ;

   virtual ~Scene() = default;

   Scene(const Scene&) = delete;

   Scene& operator=(const Scene&) = delete;

   Scene(Scene&&) = default;

   Scene& operator=(Scene&&) = default;

   virtual void Initialize() {}

   virtual void Update(double dt) {}

   virtual void Render() {}

   virtual void BeginFrame(double dt) {}

   virtual void EndFrame(double dt) {}

   virtual void Stop() {}

   template <EntityType T>
   T& CreateEntity()
   {
      const unsigned int id = ++currentEntityId;
      auto entity = std::make_unique<T>();
      entity->Id = id;
      entity->Initialize();

      T& ref = *entity;

      Entities.emplace(id, std::move(entity));

      return ref;
   }

   template <EntityType T>
   T& GetEntity(unsigned int id)
   {
      auto entity = Entities.find(id);
      if (entity == Entities.end())
      {
         throw std::runtime_error(std::format("Entity Not Found: {}", typeid(T).name()));
      }
      return static_cast<T&>((*entity->second));
   }

   void AddChild(Scene& childScene)
   {
      if (Children.contains(childScene.Name))
      {
         LoggerService::Error("Child scene already exists: " + childScene.Name);
         return;
      }

      if (&childScene == this)
      {
         LoggerService::Error("A scene cannot be its own child.");
         return;
      }

      if (Parent.Get() == &childScene)
      {
         LoggerService::Error("A scene cannot have its parent as a child.");
         return;
      }

      SafePtr<Scene> childPtr;
      childPtr = &childScene;
      Children.emplace(childScene.Name, std::move(childPtr));

      SafePtr<Scene> parentPtr;
      parentPtr = this;
      childScene.Parent = std::move(parentPtr);
   }

   void RemoveChild(const std::string& childName)
   {
      if (Children.contains(childName))
      {
         Children.at(childName)->Parent.Reset();
         Children.erase(childName);
      }
      else
      {
         LoggerService::Error("Scene Doesn't Have Child Named: " + childName);
      }
   }

   std::vector<SafePtr<Entity>> GetEntities()
   {
      std::vector<SafePtr<Entity>> entities;
      entities.reserve(Entities.size());

      RecursiveEntities(entities);

      return entities;
   }

   std::vector<SafePtr<Scene>> GetChildren()
   {
      std::vector<SafePtr<Scene>> children;
      children.reserve(Children.size());

      for (auto& child : Children | std::views::values)
      {
         SafePtr<Scene> childPtr;
         childPtr = &*child;
         children.push_back(childPtr);
      }

      return children;
   }

private:
   unsigned int currentEntityId = 0;
   SafePtr<Scene> Parent{"Scene Has No Parent"};
   std::unordered_map<std::string, SafePtr<Scene>> Children;

   void RecursiveEntities(std::vector<SafePtr<Entity>>& entities)
   {
      for (auto& entity : Entities | std::views::values)
      {
         SafePtr<Entity> entityPtr;
         entityPtr = &*entity;
         entities.push_back(entityPtr);
      }

      for (auto& child : Children | std::views::values)
      {
         child->RecursiveEntities(entities);
      }
   }
};
