#pragma once

namespace Math {
   inline constexpr float EPSILONF = 1e-5f;
   inline constexpr double EPSILOND = 1e-9;

   float Radians(float deg);

   float Degrees(float rad);

   bool NearlyEquals(float a, float b, float epsilon = EPSILONF);
} // namespace Math
