#pragma once
#include "Core/OuterCore/Component.hpp"
#include "Modules/Renderer/Resources/Mesh.hpp"
#include "Utilities/SafePtr.hpp"

struct MeshComponent : Component {
    SafePtr<Mesh> Mesh{"Mesh Component Has No Mesh Assigned"};
};
