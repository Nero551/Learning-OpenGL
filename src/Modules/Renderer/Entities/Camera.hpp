#pragma once

#include "Core/Entity.hpp"
#include "Modules/Renderer/Components/CameraComponent.hpp"
#include "Modules/Renderer/Components/TransformComponent.hpp"
#include "Utilities/Services/LoggerService.hpp"

struct Camera : Entity {
  void Initialize() override {
    AddComponent<CameraComponent>();
    AddComponent<TransformComponent>();
  }
};