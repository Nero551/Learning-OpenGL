#include "../OpenGL.h"
#include "Renderer.h"
#include <GL/gl.h>

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices)
    : Vertices(vertices), Indices(indices) {

  Id = CreateVAO();
  VBO = CreateVBO();
  EBO = CreateEBO();
  SetupVertAttrPointers();
}

void Mesh::Draw() {
  glBindVertexArray(Id);
  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
}

unsigned int Mesh::CreateVAO() {
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  return VAO;
}

unsigned int Mesh::CreateVBO() {
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), Vertices.data(), GL_STATIC_DRAW);

  return VBO;
}

unsigned int Mesh::CreateEBO() {
  unsigned int EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), Indices.data(), GL_STATIC_DRAW);

  return EBO;
}

void Mesh::SetupVertAttrPointers() {
  // Position
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Position));
  glEnableVertexAttribArray(0);

  // Color
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Color));
  glEnableVertexAttribArray(1);

  // UV
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, UV));
  glEnableVertexAttribArray(2);
}
