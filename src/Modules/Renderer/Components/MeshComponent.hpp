#pragma once
#include "Core/Component.hpp"
#include "Modules/Renderer/Resources/Mesh.hpp"

struct MeshComponent : Component {
   SafePtr<Mesh> Mesh{"Mesh Component Has No Mesh"};
};
