#pragma once

#include "Entity.hpp"
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


    virtual void Initialize() {}

    virtual void Update(double dt) {}

    virtual void FixedUpdate(double fdt) {}

    virtual void Render() {}

    virtual void BeginFrame(double dt) {}

    virtual void EndFrame(double dt) {}

    virtual void Stop() {}

    Entity& GetActiveCamera();
    void SetActiveCamera(Entity& entity);
    void SetRoot(Entity&);
    bool IsRoot(unsigned int Id);
    Entity& GetRoot();

private:
    CheckedPtr<Entity> ActiveCamera{"Scene Has No Active Camera Assigned"};
    CheckedPtr<Entity> Root{"Scene Has No Root"};
};
