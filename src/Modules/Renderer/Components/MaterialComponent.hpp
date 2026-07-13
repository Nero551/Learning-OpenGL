#pragma once
#include "Core/Component.hpp"
#include "Modules/Renderer/Resources/Material.hpp"
#include "Utilities/Services/LoggerService.hpp"

struct MaterialComponent : Component {

   Material &GetMaterial() {
      return LoggerService::Require(Material, "Material Component Has No Material Assigned");
   }

   void SetMaterial(Material &material) { Material = &material; }

private:
   Material *Material = nullptr;
};
