#pragma once
#include "Entity.hpp"
#include "Modules/Renderer/Camera.hpp"

template <typename T>
concept EntityType = std::derived_from<T, Entity>;

struct Scene {
  Camera *ActiveCamera;
  std::unordered_map<unsigned int, Entity> Entities;

  template <EntityType T> T CreateEntity() {
    if (id >= max) {
      return NULL;
    }

    T entity(id);
    Entities.insert({id, entity});

    id++;

    return entity;
  }

private:
  unsigned int id = 1;
  unsigned int max = 10000;
};