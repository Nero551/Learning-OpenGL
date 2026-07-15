#pragma once
#include "../Vertex.hpp"
#include "Core/OuterCore/Resource.hpp"

#include <vector>

#include "../Enums/Topology.hpp"

struct Mesh : Resource
{
    bool Wireframe = false;
    Topology Topology = Topology::Triangles;

    Mesh(const std::string& name, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

    ~Mesh() override;

    unsigned int GetId() const;

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
