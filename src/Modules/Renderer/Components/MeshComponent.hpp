#pragma once
#include "Core/OuterCore/ECS/Component.hpp"
#include "Modules/Renderer/Resources/Mesh.hpp"
#include "Utilities/CheckedPtr.hpp"

namespace E {
struct MeshComponent : Component {
    U::CheckedPtr<Mesh> Mesh{"Mesh Component Has No Mesh Assigned"};
};
}
