#include <OpenGL.hpp>

#include "Core/InnerCore/Engine.hpp"
#include "Utilities/Math/Quaternion.hpp"

static void Testing() {
    // E::M::Quaternion q1 = {1, 1, 1, 1};
    // E::M::Quaternion q2 = {1, 0, 0, 1};
    //
    // E::U::Logger::Info(q2);
}

int main() {
    // Testing();
    // return 0;

    E::Engine::PreInit();
    E::Engine engine;

    engine.Start();

    double accumulator = 0;

    while (engine.Running) {
        engine.BeginFrame();

        accumulator += engine.DeltaTime;
        accumulator = std::min(accumulator, 0.25);

        while (accumulator >= engine.FixedDeltaTime) {
            engine.FixedUpdate();
            accumulator -= engine.FixedDeltaTime;
        }

        engine.Update();
        engine.Render();

        engine.EndFrame();
    }

    engine.Stop();
    return 0;
}
