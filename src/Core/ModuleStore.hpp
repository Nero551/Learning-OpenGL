#pragma once
#include "Modules/Input/Input.hpp"
#include "../Modules/Renderer/Renderer.hpp"

struct ModuleStore {
  // Modules Go in here.

  Renderer RendererModule;
  Input InputModule;
};