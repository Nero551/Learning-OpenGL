#pragma once
#include "Entity.hpp"
#include "Modules/Renderer/Camera.hpp"

template <typename T>
concept EntityType = std::derived_from<T, Entity>;

struct Scene {
  Camera *ActiveCamera = nullptr;
  Camera camera;
  std::unordered_map<unsigned int, Entity> Entities;

  virtual void Start() {}
  virtual void Update(double dt) {}
  virtual void Stop() {}
  virtual ~Scene() {}

  void SetActiveCamera(Camera &camera) { ActiveCamera = &camera; }

  template <EntityType T> T CreateEntity() {
    if (id >= max) {
      return NULL;
    }

    T entity(id);
    entity.Initialize();
    Entities.insert({id, entity});

    id++;

    return entity;
  }

private:
  unsigned int id = 1;
  unsigned int max = 10000;
};