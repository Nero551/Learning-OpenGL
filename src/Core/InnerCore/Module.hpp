#pragma once

#include "SystemOwner.hpp"

struct Module : SystemOwner {
    void Start();

    void Update(double dt);

    void FixedUpdate(double fdt);

    void Stop();

    void Render();

    void BeginFrame(double dt);

    void EndFrame(double dt);

    Module() = default;

    Module(const Module&) = delete;

    Module& operator=(const Module&) = delete;

    Module(Module&&) = default;

    Module& operator=(Module&&) = default;

protected:
    virtual void OnStart() {}
    virtual void OnUpdate(double dt) {}
    virtual void OnFixedUpdate(double fdt) {}
    virtual void OnEndFrame(double dt) {}
    virtual void OnRender() {}
    virtual void OnBeginFrame(double dt) {}
    virtual void OnStop() {}
};
