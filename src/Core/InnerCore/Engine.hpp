#pragma once
#include "../Services/EventBus.hpp"
#include "Module.hpp"
#include "../Services/ResourceManager.hpp"
#include "Window.hpp"
#include "World.hpp"
#include "Utilities/SafePtr.hpp"

template <typename T>concept ModuleType = std::derived_from<T, Module>;

struct Engine {
    static SafePtr<Engine> Ins;

    bool Running;
    double Time = 0;
    double DeltaTime = 0;

    Window Window;
    World World;

    Engine();

    void Start();

    void Stop();

    void BeginFrame();

    void EndFrame();

    void Update();

    void Render();

    template <ModuleType T> T& GetModule() {
        auto module = Modules.find(typeid(T));
        if (module == Modules.end()) { Logger::Fatal(std::format("Module {} not found", typeid(T).name())); }
        return static_cast<T&>((*module->second));
    }

private:
    void AddModules();

    std::unordered_map<std::type_index, std::unique_ptr<Module>> Modules;

    template <ModuleType T> T& AddModule() {
        auto module = std::make_unique<T>();
        Modules.emplace(typeid(T), std::move(module));
        return static_cast<T&>(*Modules.find(typeid(T))->second);
    }

    void AddServices();

    double LastFrame = 0;
};
