#pragma once
#include <functional>
#include <memory>
#include <ranges>
#include <typeindex>
#include <unordered_map>

#include "Event.hpp"

template <typename T> concept EventType = std::derived_from<T, Event> ;

struct EventBus {
    template <EventType T, typename... Args> void Fire(Args&&... args) {
        T event{std::forward<Args>(args)...};

        auto listeners = Listeners.find(typeid(T));
        if (listeners == Listeners.end()) { return; }

        for (auto& callback : listeners->second) { callback(event); }
    }

    template <EventType T> void Sub(const std::function<void(T&)>& callback) {
        auto method = [callback](Event& e) { callback(static_cast<T&>(e)); };

        if (Listeners.contains(typeid(T))) { Listeners[typeid(T)].emplace_back(method);; }
        else {
            std::vector<std::function<void(Event&)>> listeners;
            listeners.emplace_back(method);
            Listeners.emplace(typeid(T), listeners);
        }
    }

    template <EventType T> void UnSub() {}

private:
    std::unordered_map<std::type_index, std::vector<std::function<void(Event&)>>> Listeners;
};
