#include <OpenGL.hpp>

#include "Core/InnerCore/Engine.hpp"
#include "Math/Common/Exponentials.hpp"
#include "Math/Complex.hpp"
#include "Math/Functions/Function.hpp"
#include "Math/Quaternion.hpp"

static void Testing() {
    // E::M::Quaternion q1 = {1, 1, 1, 1};
    // E::M::Quaternion q2 = {1, 0, 0, 1};
    //
    // E::U::Logger::Info(q2);

    // E::M::Complex c = {1, 2};
    // E::U::Logger::Info(c);

    E::M::Function cosine = [](const float x) { return std::cos(x); };
    E::U::Logger::Info(cosine(0.6));
    E::U::Logger::Info("[TAYLOR] ", cosine.Taylor(4, 0.5)(0.6));
}

int main() {
    Testing();
    return 0;
    E::Engine engine;
    engine.Run();
    return 0;
}
