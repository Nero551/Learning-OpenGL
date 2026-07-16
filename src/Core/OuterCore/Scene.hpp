#pragma once

#include "Entity.hpp"
#include "Utilities/SafePtr.hpp"

#include "Modules/Renderer/Components/LightComponent.hpp"

template <typename T>concept EntityType = std::derived_from<T, Entity>;

struct Scene {
    std::string Name;
    const int MaxLights = 10;
    SafePtr<Entity> Root{"Scene Has No Root"};

    Scene() = default ;

    virtual ~Scene() = default;

    Scene(const Scene&) = delete;

    Scene& operator=(const Scene&) = delete;

    Scene(Scene&&) = default;


    virtual void Initialize() {}

    virtual void Update(double dt) {}

    virtual void Render() {}

    virtual void BeginFrame(double dt) {}

    virtual void EndFrame(double dt) {}

    virtual void Stop() {}

    Entity& GetActiveCamera();
    void SetActiveCamera(Entity& entity);

private:
    SafePtr<Entity> ActiveCamera{"Scene Has No Active Camera Assigned"};
};
