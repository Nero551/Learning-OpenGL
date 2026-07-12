#pragma once
#include "../Vertex.hpp"
#include "Core/Resource.hpp"

#include <vector>

struct Mesh : Resource {
   Mesh(const std::string &name, const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);

   unsigned int GetId() const { return Id; };

   void Draw();

private:
   unsigned int VBO;
   unsigned int EBO;

   unsigned int CreateVAO();

   unsigned int CreateVBO();

   unsigned int CreateEBO();

   void SetupVertAttrPointers();

protected:
   unsigned int Id;
   std::vector<Vertex> Vertices;
   std::vector<unsigned int> Indices;
};
