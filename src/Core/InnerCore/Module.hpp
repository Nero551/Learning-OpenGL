#pragma once

#include "../OuterCore/System.hpp"
#include "Utilities/Logger.hpp"

template <typename T>concept SystemType = std::derived_from<T, System>;

struct Module {
    void Start();

    void Update(double dt);

    void FixedUpdate(double fdt);

    void Stop();

    void Render();

    void BeginFrame(double dt);

    void EndFrame(double dt);

    virtual ~Module() = default;

    template <SystemType T> T& GetSystem() {
        auto system = Systems.find(typeid(T));
        if (system == Systems.end()) { Logger::Fatal(std::format("System Not Found: {}", typeid(T).name())); }
        return static_cast<T&>(*system->second);
    }

    Module() = default;

    Module(const Module&) = delete;

    Module& operator=(const Module&) = delete;

    Module(Module&&) = default;

    Module& operator=(Module&&) = default;

private:
    std::unordered_map<std::type_index, std::unique_ptr<System>> Systems;
    virtual void AddSystems() {}

protected:
    virtual void OnStart() {}
    virtual void OnUpdate(double dt) {}
    virtual void OnFixedUpdate(double fdt) {}
    virtual void OnEndFrame(double dt) {}
    virtual void OnRender() {}
    virtual void OnBeginFrame(double dt) {}
    virtual void OnStop() {}

    template <SystemType T> T& AddSystem() {
        if (Systems.contains(std::type_index(typeid(T)))) { Logger::Fatal("System Already Exists"); }

        auto system = std::make_unique<T>();
        T& ref = *system;
        Systems.emplace(typeid(T), std::move(system));
        return ref;
    }
};
