#pragma once
#include "Entity.hpp"
#include "Modules/Renderer/Entities/Camera.hpp"
#include <unordered_map>
#include <vector>

template <typename T>
concept EntityType = std::derived_from<T, Entity>;

struct Scene {
  std::string Name;
  Camera *ActiveCamera = nullptr;
  std::unordered_map<unsigned int, std::unique_ptr<Entity> > Entities;

  Scene() = default;

  virtual void Initialize() {
  }

  virtual ~Scene() {
  }

  void SetActiveCamera(Camera &camera) { ActiveCamera = &camera; }

  template <EntityType T> T &CreateEntity() {
    auto entity = std::make_unique<T>();
    entity->Id = id;
    entity->Initialize();

    T &ref = *entity;

    Entities.insert({id, std::move(entity)});

    id++;

    return ref;
  }

  auto begin() { return Entities.begin(); }
  auto end() { return Entities.end(); }

  auto begin() const { return Entities.begin(); }
  auto end() const { return Entities.end(); }

private:
  unsigned int id = 1;
};