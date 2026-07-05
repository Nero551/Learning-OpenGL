#include "MathUtils.hpp"
#include <numbers>

float Math::DegToRad(float deg) {
  return deg * std::numbers::pi / 180;
}
float Math::RadToDeg(float rad) {
  return rad * 180 / std::numbers::pi;
}