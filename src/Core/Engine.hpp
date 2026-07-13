#pragma once
#include "Module.hpp"
#include "ResourceManager.hpp"
#include "Window.hpp"
#include "Core/World.hpp"

template<typename T>concept ModuleType = std::derived_from<T, Module>;

struct Engine {
   static SafePtr<Engine> Ins;

   bool Running;
   double Time = 0;
   double DeltaTime = 0;

   Window Window;
   World World;
   ResourceManager ResourceManager;

   Engine();

   void Start();

   void Stop();

   void BeginFrame();

   void EndFrame();

   void Update();

   void Render();

   template<ModuleType T> T &GetModule() {
      auto module = Modules.find(typeid(T));
      if (module == Modules.end()) {
         throw std::runtime_error(std::format("Module Not Found: {}", typeid(T).name()));
      }
      return static_cast<T &>((*module->second));
   }

private:
   void AddModules();

   std::unordered_map<std::type_index, std::unique_ptr<Module> > Modules;

   template<ModuleType T> T &AddModule() {
      auto module = std::make_unique<T>();
      T &ref = *module;
      Modules.emplace(typeid(T), std::move(module));
      return ref;
   }

   double LastFrame = 0;
};
