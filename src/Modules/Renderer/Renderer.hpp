#pragma once

#include "Core/InnerCore/Module.hpp"

struct Renderer : Module {
protected:
   void OnRender() override;

private:
   void AddSystems() override;
};
