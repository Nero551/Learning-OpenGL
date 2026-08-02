#pragma once

#include "ECS/Entity.hpp"
#include "Utilities/CheckedPtr.hpp"

#include "Modules/Renderer/Components/LightComponent.hpp"

struct Scene {
    std::string Name;
    int MaxLights = 10;

    Scene() = default ;

    virtual ~Scene() = default;

    Scene(const Scene&) = delete;

    Scene& operator=(const Scene&) = delete;

    Scene(Scene&&) = default;

    virtual void Update(double dt) {}

    virtual void FixedUpdate(double fdt) {}

    virtual void Render() {}

    virtual void BeginFrame(double dt) {}

    virtual void EndFrame(double dt) {}

    virtual void Stop() {}

    E::Entity& GetActiveCamera();
    void SetActiveCamera(E::Entity& entity);
    void SetRoot(E::Entity&);
    bool IsRoot(unsigned int id);
    E::Entity& GetRoot();

private:
    CheckedPtr<E::Entity> ActiveCamera{"Scene Has No Active Camera Assigned"};
    CheckedPtr<E::Entity> Root{"Scene Has No Root"};
};
