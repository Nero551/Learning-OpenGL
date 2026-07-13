#include <OpenGL.hpp>
#include "Mesh.hpp"

Mesh::Mesh(const std::string &name, const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices) : Resource(name),
   Vertices(vertices), Indices(indices) {
   Id = CreateVAO();
   VBO = CreateVBO();
   EBO = CreateEBO();
   SetupVertAttrPointers();
   glBindVertexArray(0);
}

void Mesh::Draw() {
   if (Wireframe) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   } else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   }

   glBindVertexArray(Id);
   glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, nullptr);
}

unsigned int Mesh::CreateVAO() {
   unsigned int VAO;
   glGenVertexArrays(1, &VAO);
   glBindVertexArray(VAO);

   return VAO;
}

unsigned int Mesh::CreateVBO() {
   unsigned int vbo;
   glGenBuffers(1, &vbo);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), Vertices.data(), GL_STATIC_DRAW);

   return vbo;
}

unsigned int Mesh::CreateEBO() {
   unsigned int ebo;
   glGenBuffers(1, &ebo);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), Indices.data(), GL_STATIC_DRAW);

   return ebo;
}

void Mesh::SetupVertAttrPointers() {
   // Position
   glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, Position)));
   glEnableVertexAttribArray(0);

   // Color
   glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, Color)));
   glEnableVertexAttribArray(1);

   // UV
   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, UV)));
   glEnableVertexAttribArray(2);

   //Normal
   glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, Normal)));
   glEnableVertexAttribArray(3);
}
