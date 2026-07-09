#pragma once
#include "Entity.hpp"
#include <unordered_map>
#include <concepts>

template <typename T>
concept EntityType = std::derived_from<T, Entity>;

struct World {
  // TODO- this guy should own runtime world state (stuff that exist).
  std::unordered_map<unsigned int, Entity> Entities;

  template <EntityType T> void CreateEntity() {
    if (id >= max) {
      return;
    }

    T entity(id);
    Entities.insert({id, entity});

    id++;
  }

private:
  unsigned int id = 0;
  unsigned int max = 10000;
};
