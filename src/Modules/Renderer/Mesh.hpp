#pragma once
#include "Vertex.hpp"

#include <vector>

class Mesh {
public:
  unsigned int Id;
  std::vector<Vertex> Vertices;
  std::vector<unsigned int> Indices;

  Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices);
  void Draw();

private:
  unsigned int VBO;
  unsigned int EBO;

  unsigned int CreateVAO();
  unsigned int CreateVBO();
  unsigned int CreateEBO();
  void SetupVertAttrPointers();
};