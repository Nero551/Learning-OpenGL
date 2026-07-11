#pragma once
#include <memory>
#include <vector>

#include "Core/Scene.hpp"
#include "System.hpp"

template<typename T>concept SceneType = std::derived_from<T, Scene>;

template<typename T>concept SystemType = std::derived_from<T, System>;

struct World {
   Scene *ActiveScene = nullptr;

   template<SceneType T> T &CreateScene(const std::string &name) {
      auto scene = std::make_unique<T>();
      scene->Name = name;
      scene->Initialize();
      T &ref = *scene;
      Scenes.emplace(name, std::move(scene));
      return ref;
   }

   template<SceneType T> T &GetScene(const std::string &name) {
      auto scene = Scenes.find(name);
      if (scene == Scenes.end()) { throw std::runtime_error("No corresponding Scene."); }
      return static_cast<T &>(*scene->second);
   }

   void SetActiveScene(Scene &scene) { ActiveScene = &scene; }

   template<SceneType T = Scene> T &GetActiveScene() { return static_cast<T &>(*ActiveScene); }

   template<SystemType T> T &AddSystem() {
      if (Systems.contains(std::type_index(typeid(T)))) {
         throw std::runtime_error("System already exists.");
      }

      auto system = std::make_unique<T>();
      T &ref = *system;
      Systems.emplace(typeid(T), std::move(system));
      return ref;
   }

   template<SystemType T> T &GetSystem() {
      auto system = Systems.find(typeid(T));
      if (system == Systems.end()) {
         throw std::runtime_error(std::format("System Not Found: {}", typeid(T).name()));
      }
      return static_cast<T &>((*system->second));
   }

   void Start();

   void Update(double dt);

   void Stop();

   void BeginFrame(double dt);

   void EndFrame(double dt);

private:
   void AddSystems();

   std::unordered_map<std::string, std::unique_ptr<Scene> > Scenes;
   std::unordered_map<std::type_index, std::unique_ptr<System> > Systems;
};
