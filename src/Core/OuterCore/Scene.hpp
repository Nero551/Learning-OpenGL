#pragma once

#include "ECS/Entity.hpp"
#include "Utilities/CheckedPtr.hpp"

namespace E {
struct Scene {
    CheckedPtr<Entity> Root{"Scene Has No Root"};

    Scene() = default ;

    virtual ~Scene() = default;

    Scene(const Scene&) = delete;

    Scene& operator=(const Scene&) = delete;

    Scene(Scene&&) = default;
};
}
