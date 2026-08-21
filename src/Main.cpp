#include <OpenGL.hpp>

#include "Core/InnerCore/Engine.hpp"
#include "Math/Common/Quaternion.hpp"
#include "Math/Complex.hpp"

static void Testing() {
    // E::M::Quaternion q1 = {1, 1, 1, 1};
    // E::M::Quaternion q2 = {1, 0, 0, 1};
    //
    // E::U::Logger::Info(q2);

    E::M::Complex c = { 1, 2 };

    E::U::Logger::Info(c);
}

int main() {
    Testing();
    return 0;
    E::Engine engine;
    engine.Run();
    return 0;
}
