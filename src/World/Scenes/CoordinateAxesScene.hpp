#pragma once

#include "Core/Scene.hpp"

struct CoordinateAxesScene : Scene
{
   void Initialize() override;

   void Update(double dt) override;
};
