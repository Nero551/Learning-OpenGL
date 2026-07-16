#pragma once
#include "Core/OuterCore/Component.hpp"
#include "Modules/Renderer/Resources/Mesh.hpp"
#include "Utilities/CheckedPtr.hpp"

struct MeshComponent : Component {
    CheckedPtr<Mesh> Mesh{"Mesh Component Has No Mesh Assigned"};
};
