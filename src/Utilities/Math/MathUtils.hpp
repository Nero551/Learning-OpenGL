#pragma once

namespace Math {
   constexpr float EPSILONF = 1e-6f;
   constexpr double EPSILOND = 1e-9;

   float Radians(float deg);

   float Degrees(float rad);

   bool NearlyEquals(float a, float b);

} // namespace Math
