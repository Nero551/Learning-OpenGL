#include "Engine/Engine.h"
#include <chrono>

using Clock = std::chrono::steady_clock;

const double DeltaTime = 0.016;

int main() {
  Engine engine;

  auto LastCall = Clock::now();

  engine.Running = true;
  engine.Start();

  while (engine.Running) {
    auto now = Clock::now();

    if (now - LastCall >= std::chrono::milliseconds(int(DeltaTime * 1000))) {
      LastCall = now;
      engine.Time += DeltaTime;
      engine.Process(DeltaTime);
    }
  }

  engine.Stop();
  return 0;
}
