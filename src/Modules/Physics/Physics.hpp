#pragma once

#include "Core/InnerCore/Module.hpp"

namespace E {
struct Physics : Module {
protected:
    void OnStart() override;
    void OnFixedUpdate(double fdt) override;
    void AddSystems() override;
};
} // namespace E
