#pragma once
#include "Service.hpp"
#include "../Services/EventBus.hpp"
#include "Utilities/CheckedPtr.hpp"

template <typename T> concept ServiceType = std::derived_from<T, Service>;

struct ServiceStore {
    static CheckedPtr<ServiceStore> Ins;

    ServiceStore() {
        Ins = this;
    }

    template <ServiceType T> T& Add() {
        if (Services.contains(typeid(T))) {
            Logger::Error(std::format("ServiceStore already contains Service {}", typeid(T).name()));
            return static_cast<T&>((*Services.at(typeid(T))));
        }

        auto service = std::make_unique<T>();
        Services.emplace(std::type_index(typeid(T)), std::move(service));

        return Get<T>();
    }

    template <ServiceType T> T& Get() {
        auto service = Services.find(typeid(T));
        if (service == Services.end()) {
            Logger::Fatal(std::format("Service Not Found: {}", typeid(T).name()));
        }
        return static_cast<T&>((*service->second));
    }

private:
    std::unordered_map<std::type_index, std::unique_ptr<Service>> Services;
};
