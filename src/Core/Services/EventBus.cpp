#include "EventBus.hpp"


void EventBus::EmptyFireQueue() {
    for (auto& event : FireQueue) {
        auto listeners = Listeners.find(typeid(*event));
        if (listeners == Listeners.end()) { continue; }

        for (auto& callback : listeners->second) { callback(*event); }
    }
    FireQueue.clear();
}
