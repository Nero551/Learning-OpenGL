#pragma once

#include "Core/Module.hpp"

struct Renderer : Module {
protected:
   void OnRender() override;

private:
   void AddSystems() override;
};
