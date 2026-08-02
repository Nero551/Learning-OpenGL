#pragma once
#include "Utilities/CheckedPtr.hpp"
#include "Utilities/Logger.hpp"

struct Service;
template <typename T> concept ServiceType = std::derived_from<T, Service>;

struct Service {
    template <ServiceType T> static T& Add() {
        if (Services.contains(typeid(T))) {
            Logger::Error(std::format("Service already contains Service {}", typeid(T).name()));
            return static_cast<T&>(*Services.at(typeid(T)));
        }

        auto service = std::make_unique<T>();
        Services.emplace(std::type_index(typeid(T)), std::move(service));

        return Get<T>();
    }

    template <ServiceType T> static T& Get() {
        auto service = Services.find(typeid(T));
        if (service == Services.end()) {
            Logger::Fatal(std::format("Service Not Found: {}", typeid(T).name()));
        }
        return static_cast<T&>(*service->second);
    }

    static std::vector<CheckedPtr<Service>> GetAll() {
        std::vector<CheckedPtr<Service>> services;

        for (auto& service : Services | std::views::values) {
            services.emplace_back(&*service);
        }
        return services;
    }

private:
    inline static std::unordered_map<std::type_index, std::unique_ptr<Service>> Services;
};
