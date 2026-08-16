#pragma once

namespace E {
/**
 * @brief Base class for resources managed by ResourceManager.
 *
 * Provides a name shared by all resource types and establishes
 * polymorphic destruction through a virtual destructor.
 * Resources are non-copyable but movable.
 */
struct Resource {
    std::string Name;

    virtual ~Resource() = default;

    Resource(std::string name) : Name(std::move(name)) {};

    Resource(const Resource&) = delete;

    Resource& operator=(const Resource&) = delete;

    Resource(Resource&&) = default;

    Resource& operator=(Resource&&) = default;
};
} // namespace E
