#pragma once
#include "Core/Component.hpp"
#include "Modules/Renderer/Resources/Mesh.hpp"

struct MeshComponent : Component {
   Mesh &GetMesh() { return LoggerService::Require(Mesh, "Mesh Component Has No Mesh Assigned"); }
   void SetMesh(Mesh &mesh) { Mesh = &mesh; }

private:
   Mesh *Mesh = nullptr;
};
