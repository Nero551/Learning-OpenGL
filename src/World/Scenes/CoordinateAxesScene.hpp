#pragma once

#include "Core/OuterCore/Scene.hpp"

struct CoordinateAxesScene : Scene
{
   void Initialize() override;

   void Update(double dt) override;
};
