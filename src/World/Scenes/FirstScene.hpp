#pragma once
#include "Core/OuterCore/Scene.hpp"

struct FirstScene : Scene {
   void Initialize() override;

   void Update(double dt) override;
};
