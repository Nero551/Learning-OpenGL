#pragma once

#include "Core/InnerCore/Module.hpp"

namespace E {
    struct Renderer : Module {
    protected:
        void OnRender() override;

    private:
        void AddSystems() override;
    };
}