#pragma once
#include "Core/OuterCore/System.hpp"
#include "Utilities/Logger.hpp"

template <typename T>concept SystemType = std::derived_from<T, System>;

struct SystemOwner {
    virtual ~SystemOwner() = default;

    template <SystemType T> T& GetSystem() {
        auto system = Systems.find(typeid(T));
        if (system == Systems.end()) {
            Logger::Fatal(std::format("System Not Found: {}", typeid(T).name()));
        }
        return static_cast<T&>(*system->second);
    }

protected:
    std::unordered_map<std::type_index, std::unique_ptr<System>> Systems;
    virtual void AddSystems() {}

    template <SystemType T> T& AddSystem() {
        if (Systems.contains(std::type_index(typeid(T)))) {
            Logger::Fatal("System Already Exists");
        }

        auto system = std::make_unique<T>();
        T& ref = *system;
        Systems.emplace(typeid(T), std::move(system));
        return ref;
    }
};