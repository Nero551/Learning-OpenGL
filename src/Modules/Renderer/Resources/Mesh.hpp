#pragma once
#include "../Vertex.hpp"
#include "Core/Resource.hpp"

#include <vector>

class Mesh : Resource {
public:
  unsigned int Id;
  std::vector<Vertex> Vertices;
  std::vector<unsigned int> Indices;

  Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);
  void Draw();

private:
  unsigned int VBO;
  unsigned int EBO;

  unsigned int CreateVAO();
  unsigned int CreateVBO();
  unsigned int CreateEBO();
  void SetupVertAttrPointers();
};