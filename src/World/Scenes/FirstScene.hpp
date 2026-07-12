#pragma once
#include "Core/Scene.hpp"

struct FirstScene : Scene {
   void Initialize() override;

   void Update(double dt) override;
};
