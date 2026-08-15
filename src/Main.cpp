#include <OpenGL.hpp>

#include "Core/InnerCore/Engine.hpp"
#include "Math/Common/Quaternion.hpp"

static void Testing() {
    // E::M::Quaternion q1 = {1, 1, 1, 1};
    // E::M::Quaternion q2 = {1, 0, 0, 1};
    //
    // E::U::Logger::Info(q2);
}

int main() {
    // Testing();
    // return 0;

    E::Engine::Create().Run();
    return 0;
}
