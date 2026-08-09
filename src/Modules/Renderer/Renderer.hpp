#pragma once

#include "Core/InnerCore/Module.hpp"

namespace E {
struct Renderer : Module {
protected:
    void OnStart() override;
    void OnBeginFrame(double dt) override;
    void OnRender() override;

private:
    void AddSystems() override;
};
}
