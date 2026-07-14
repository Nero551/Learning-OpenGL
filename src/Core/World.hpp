#pragma once
#include <memory>
#include <vector>

#include "Scene.hpp"
#include "Core/Scene.hpp"
#include "Utilities/Services/LoggerService.hpp"

template <typename T>concept SceneType = std::derived_from<T, Scene>;

struct World
{
   SafePtr<Scene> ActiveScene;

   template <SceneType T>
   T& CreateScene(const std::string& name)
   {
      auto scene = std::make_unique<T>();
      scene->Name = name;
      scene->Initialize();
      T& ref = *scene;
      Scenes.emplace(name, std::move(scene));
      return ref;
   }

   template <SceneType T>
   T& GetScene(const std::string& name)
   {
      auto scene = Scenes.find(name);
      if (scene == Scenes.end()) { throw std::runtime_error("No corresponding Scene."); }
      return static_cast<T&>(*scene->second);
   }

   void Start();

   void Update(double dt);

   void Stop();

   void BeginFrame(double dt);

   void EndFrame(double dt);

   void Render();

private:
   std::unordered_map<std::string, std::unique_ptr<Scene>> Scenes;
};
