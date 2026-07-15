#include "Profiling.hpp"

#include "Core/InnerCore/Engine.hpp"

void Profiling::AddSystems() {}

void Profiling::OnStart() {}

double elapsed;

void Profiling::OnUpdate(double dt) {
   elapsed += dt;

   FrameMs = dt * 1000.0;
   FrameCount++;

   if (FrameTimes.size() > 60) {
      FrameTimes.pop_front();
   }
   FrameTimes.push_back(dt * 1000.0);

   if (elapsed >= 1.0) {
      elapsed = 0.0;

      double sum = 0.0;

      for (double frame: FrameTimes) sum += frame;

      double averageFrameMs = sum / FrameTimes.size();

      Engine::Ins->Window.SetTitle(
         "FPS: " + std::to_string(FrameCount) + " | " + "AVG: " + std::to_string(averageFrameMs) + " ms" + " | " +
         std::to_string(FrameMs) + " ms");
      FrameCount = 0;
   }
}
