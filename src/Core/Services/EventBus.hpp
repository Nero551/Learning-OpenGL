#pragma once
#include <functional>
#include <memory>
#include <ranges>
#include <typeindex>
#include <unordered_map>

#include "../OuterCore/Event.hpp"
#include "Core/OuterCore/Service.hpp"
#include "Utilities/Logger.hpp"

template <typename T> concept EventType = std::derived_from<T, Event> ;

struct EventBus : Service {
    template <EventType T, typename... Args> void InstantFire(Args&&... args) {
        auto listeners = Listeners.find(typeid(T));
        if (listeners == Listeners.end()) { return; }

        T event{std::forward<Args>(args)...};
        for (auto& callback : listeners->second) { callback(event); }
    }

    template <EventType T, typename... Args> void Fire(Args&&... args) {
        auto event = std::make_unique<T>(std::forward<Args>(args)...);
        FireQueue.emplace_back(std::move(event));
    }

    void EmptyFireQueue();


    template <EventType T> void Sub(const std::function<void(T&)>& callback) {
        auto method = [callback](Event& e) { callback(static_cast<T&>(e)); };

        Listeners[typeid(T)].emplace_back(method);
    }

    template <EventType T> void UnSub(const std::function<void(T&)>& callback) {}

private:
    std::unordered_map<std::type_index, std::vector<std::function<void(Event&)>>> Listeners;
    std::vector<std::unique_ptr<Event>> FireQueue;
};
