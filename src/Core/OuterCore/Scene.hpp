#pragma once

#include "ECS/Entity.hpp"
#include "Utilities/CheckedPtr.hpp"

namespace E {
/**
 * @brief Temporary container for a group of entities.
 */
struct Scene {
    /** @brief Root entity of the scene hierarchy. */
    U::CheckedPtr<Entity> Root{"Scene Has No Root"};

    Scene() = default;
    virtual ~Scene() = default;

    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;

    Scene(Scene&&) = default;
};
} // namespace E
