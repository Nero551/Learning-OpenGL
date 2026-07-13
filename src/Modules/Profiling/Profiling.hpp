#pragma once

#include <deque>
#include <vector>

#include "Core/Module.hpp"

struct Profiling : Module {
   double FrameMs;
   int FrameCount;

protected:
   void OnStart() override;

   void OnUpdate(double dt) override;

private:
   std::deque<double> FrameTimes;
   
   void AddSystems() override;
};
